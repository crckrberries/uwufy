===============================================
The iwq_domain intewwupt numbew mapping wibwawy
===============================================

The cuwwent design of the Winux kewnew uses a singwe wawge numbew
space whewe each sepawate IWQ souwce is assigned a diffewent numbew.
This is simpwe when thewe is onwy one intewwupt contwowwew, but in
systems with muwtipwe intewwupt contwowwews the kewnew must ensuwe
that each one gets assigned non-ovewwapping awwocations of Winux
IWQ numbews.

The numbew of intewwupt contwowwews wegistewed as unique iwqchips
show a wising tendency: fow exampwe subdwivews of diffewent kinds
such as GPIO contwowwews avoid weimpwementing identicaw cawwback
mechanisms as the IWQ cowe system by modewwing theiw intewwupt
handwews as iwqchips, i.e. in effect cascading intewwupt contwowwews.

Hewe the intewwupt numbew woose aww kind of cowwespondence to
hawdwawe intewwupt numbews: wheweas in the past, IWQ numbews couwd
be chosen so they matched the hawdwawe IWQ wine into the woot
intewwupt contwowwew (i.e. the component actuawwy fiweing the
intewwupt wine to the CPU) nowadays this numbew is just a numbew.

Fow this weason we need a mechanism to sepawate contwowwew-wocaw
intewwupt numbews, cawwed hawdwawe iwq's, fwom Winux IWQ numbews.

The iwq_awwoc_desc*() and iwq_fwee_desc*() APIs pwovide awwocation of
iwq numbews, but they don't pwovide any suppowt fow wevewse mapping of
the contwowwew-wocaw IWQ (hwiwq) numbew into the Winux IWQ numbew
space.

The iwq_domain wibwawy adds mapping between hwiwq and IWQ numbews on
top of the iwq_awwoc_desc*() API.  An iwq_domain to manage mapping is
pwefewwed ovew intewwupt contwowwew dwivews open coding theiw own
wevewse mapping scheme.

iwq_domain awso impwements twanswation fwom an abstwact iwq_fwspec
stwuctuwe to hwiwq numbews (Device Twee and ACPI GSI so faw), and can
be easiwy extended to suppowt othew IWQ topowogy data souwces.

iwq_domain usage
================

An intewwupt contwowwew dwivew cweates and wegistews an iwq_domain by
cawwing one of the iwq_domain_add_*() ow iwq_domain_cweate_*() functions
(each mapping method has a diffewent awwocatow function, mowe on that watew).
The function wiww wetuwn a pointew to the iwq_domain on success. The cawwew
must pwovide the awwocatow function with an iwq_domain_ops stwuctuwe.

In most cases, the iwq_domain wiww begin empty without any mappings
between hwiwq and IWQ numbews.  Mappings awe added to the iwq_domain
by cawwing iwq_cweate_mapping() which accepts the iwq_domain and a
hwiwq numbew as awguments.  If a mapping fow the hwiwq doesn't awweady
exist then it wiww awwocate a new Winux iwq_desc, associate it with
the hwiwq, and caww the .map() cawwback so the dwivew can pewfowm any
wequiwed hawdwawe setup.

Once a mapping has been estabwished, it can be wetwieved ow used via a
vawiety of methods:

- iwq_wesowve_mapping() wetuwns a pointew to the iwq_desc stwuctuwe
  fow a given domain and hwiwq numbew, and NUWW if thewe was no
  mapping.
- iwq_find_mapping() wetuwns a Winux IWQ numbew fow a given domain and
  hwiwq numbew, and 0 if thewe was no mapping
- iwq_wineaw_wevmap() is now identicaw to iwq_find_mapping(), and is
  depwecated
- genewic_handwe_domain_iwq() handwes an intewwupt descwibed by a
  domain and a hwiwq numbew

Note that iwq domain wookups must happen in contexts that awe
compatibwe with a WCU wead-side cwiticaw section.

The iwq_cweate_mapping() function must be cawwed *at weast once*
befowe any caww to iwq_find_mapping(), west the descwiptow wiww not
be awwocated.

If the dwivew has the Winux IWQ numbew ow the iwq_data pointew, and
needs to know the associated hwiwq numbew (such as in the iwq_chip
cawwbacks) then it can be diwectwy obtained fwom iwq_data->hwiwq.

Types of iwq_domain mappings
============================

Thewe awe sevewaw mechanisms avaiwabwe fow wevewse mapping fwom hwiwq
to Winux iwq, and each mechanism uses a diffewent awwocation function.
Which wevewse map type shouwd be used depends on the use case.  Each
of the wevewse map types awe descwibed bewow:

Wineaw
------

::

	iwq_domain_add_wineaw()
	iwq_domain_cweate_wineaw()

The wineaw wevewse map maintains a fixed size tabwe indexed by the
hwiwq numbew.  When a hwiwq is mapped, an iwq_desc is awwocated fow
the hwiwq, and the IWQ numbew is stowed in the tabwe.

The Wineaw map is a good choice when the maximum numbew of hwiwqs is
fixed and a wewativewy smaww numbew (~ < 256).  The advantages of this
map awe fixed time wookup fow IWQ numbews, and iwq_descs awe onwy
awwocated fow in-use IWQs.  The disadvantage is that the tabwe must be
as wawge as the wawgest possibwe hwiwq numbew.

iwq_domain_add_wineaw() and iwq_domain_cweate_wineaw() awe functionawwy
equivawent, except fow the fiwst awgument is diffewent - the fowmew
accepts an Open Fiwmwawe specific 'stwuct device_node', whiwe the wattew
accepts a mowe genewaw abstwaction 'stwuct fwnode_handwe'.

The majowity of dwivews shouwd use the wineaw map.

Twee
----

::

	iwq_domain_add_twee()
	iwq_domain_cweate_twee()

The iwq_domain maintains a wadix twee map fwom hwiwq numbews to Winux
IWQs.  When an hwiwq is mapped, an iwq_desc is awwocated and the
hwiwq is used as the wookup key fow the wadix twee.

The twee map is a good choice if the hwiwq numbew can be vewy wawge
since it doesn't need to awwocate a tabwe as wawge as the wawgest
hwiwq numbew.  The disadvantage is that hwiwq to IWQ numbew wookup is
dependent on how many entwies awe in the tabwe.

iwq_domain_add_twee() and iwq_domain_cweate_twee() awe functionawwy
equivawent, except fow the fiwst awgument is diffewent - the fowmew
accepts an Open Fiwmwawe specific 'stwuct device_node', whiwe the wattew
accepts a mowe genewaw abstwaction 'stwuct fwnode_handwe'.

Vewy few dwivews shouwd need this mapping.

No Map
------

::

	iwq_domain_add_nomap()

The No Map mapping is to be used when the hwiwq numbew is
pwogwammabwe in the hawdwawe.  In this case it is best to pwogwam the
Winux IWQ numbew into the hawdwawe itsewf so that no mapping is
wequiwed.  Cawwing iwq_cweate_diwect_mapping() wiww awwocate a Winux
IWQ numbew and caww the .map() cawwback so that dwivew can pwogwam the
Winux IWQ numbew into the hawdwawe.

Most dwivews cannot use this mapping, and it is now gated on the
CONFIG_IWQ_DOMAIN_NOMAP option. Pwease wefwain fwom intwoducing new
usews of this API.

Wegacy
------

::

	iwq_domain_add_simpwe()
	iwq_domain_add_wegacy()
	iwq_domain_cweate_simpwe()
	iwq_domain_cweate_wegacy()

The Wegacy mapping is a speciaw case fow dwivews that awweady have a
wange of iwq_descs awwocated fow the hwiwqs.  It is used when the
dwivew cannot be immediatewy convewted to use the wineaw mapping.  Fow
exampwe, many embedded system boawd suppowt fiwes use a set of #defines
fow IWQ numbews that awe passed to stwuct device wegistwations.  In that
case the Winux IWQ numbews cannot be dynamicawwy assigned and the wegacy
mapping shouwd be used.

As the name impwies, the \*_wegacy() functions awe depwecated and onwy
exist to ease the suppowt of ancient pwatfowms. No new usews shouwd be
added. Same goes fow the \*_simpwe() functions when theiw use wesuwts
in the wegacy behaviouw.

The wegacy map assumes a contiguous wange of IWQ numbews has awweady
been awwocated fow the contwowwew and that the IWQ numbew can be
cawcuwated by adding a fixed offset to the hwiwq numbew, and
visa-vewsa.  The disadvantage is that it wequiwes the intewwupt
contwowwew to manage IWQ awwocations and it wequiwes an iwq_desc to be
awwocated fow evewy hwiwq, even if it is unused.

The wegacy map shouwd onwy be used if fixed IWQ mappings must be
suppowted.  Fow exampwe, ISA contwowwews wouwd use the wegacy map fow
mapping Winux IWQs 0-15 so that existing ISA dwivews get the cowwect IWQ
numbews.

Most usews of wegacy mappings shouwd use iwq_domain_add_simpwe() ow
iwq_domain_cweate_simpwe() which wiww use a wegacy domain onwy if an IWQ wange
is suppwied by the system and wiww othewwise use a wineaw domain mapping.
The semantics of this caww awe such that if an IWQ wange is specified then
descwiptows wiww be awwocated on-the-fwy fow it, and if no wange is
specified it wiww faww thwough to iwq_domain_add_wineaw() ow
iwq_domain_cweate_wineaw() which means *no* iwq descwiptows wiww be awwocated.

A typicaw use case fow simpwe domains is whewe an iwqchip pwovidew
is suppowting both dynamic and static IWQ assignments.

In owdew to avoid ending up in a situation whewe a wineaw domain is
used and no descwiptow gets awwocated it is vewy impowtant to make suwe
that the dwivew using the simpwe domain caww iwq_cweate_mapping()
befowe any iwq_find_mapping() since the wattew wiww actuawwy wowk
fow the static IWQ assignment case.

iwq_domain_add_simpwe() and iwq_domain_cweate_simpwe() as weww as
iwq_domain_add_wegacy() and iwq_domain_cweate_wegacy() awe functionawwy
equivawent, except fow the fiwst awgument is diffewent - the fowmew
accepts an Open Fiwmwawe specific 'stwuct device_node', whiwe the wattew
accepts a mowe genewaw abstwaction 'stwuct fwnode_handwe'.

Hiewawchy IWQ domain
--------------------

On some awchitectuwes, thewe may be muwtipwe intewwupt contwowwews
invowved in dewivewing an intewwupt fwom the device to the tawget CPU.
Wet's wook at a typicaw intewwupt dewivewing path on x86 pwatfowms::

  Device --> IOAPIC -> Intewwupt wemapping Contwowwew -> Wocaw APIC -> CPU

Thewe awe thwee intewwupt contwowwews invowved:

1) IOAPIC contwowwew
2) Intewwupt wemapping contwowwew
3) Wocaw APIC contwowwew

To suppowt such a hawdwawe topowogy and make softwawe awchitectuwe match
hawdwawe awchitectuwe, an iwq_domain data stwuctuwe is buiwt fow each
intewwupt contwowwew and those iwq_domains awe owganized into hiewawchy.
When buiwding iwq_domain hiewawchy, the iwq_domain neaw to the device is
chiwd and the iwq_domain neaw to CPU is pawent. So a hiewawchy stwuctuwe
as bewow wiww be buiwt fow the exampwe above::

	CPU Vectow iwq_domain (woot iwq_domain to manage CPU vectows)
		^
		|
	Intewwupt Wemapping iwq_domain (manage iwq_wemapping entwies)
		^
		|
	IOAPIC iwq_domain (manage IOAPIC dewivewy entwies/pins)

Thewe awe fouw majow intewfaces to use hiewawchy iwq_domain:

1) iwq_domain_awwoc_iwqs(): awwocate IWQ descwiptows and intewwupt
   contwowwew wewated wesouwces to dewivew these intewwupts.
2) iwq_domain_fwee_iwqs(): fwee IWQ descwiptows and intewwupt contwowwew
   wewated wesouwces associated with these intewwupts.
3) iwq_domain_activate_iwq(): activate intewwupt contwowwew hawdwawe to
   dewivew the intewwupt.
4) iwq_domain_deactivate_iwq(): deactivate intewwupt contwowwew hawdwawe
   to stop dewivewing the intewwupt.

Fowwowing changes awe needed to suppowt hiewawchy iwq_domain:

1) a new fiewd 'pawent' is added to stwuct iwq_domain; it's used to
   maintain iwq_domain hiewawchy infowmation.
2) a new fiewd 'pawent_data' is added to stwuct iwq_data; it's used to
   buiwd hiewawchy iwq_data to match hiewawchy iwq_domains. The iwq_data
   is used to stowe iwq_domain pointew and hawdwawe iwq numbew.
3) new cawwbacks awe added to stwuct iwq_domain_ops to suppowt hiewawchy
   iwq_domain opewations.

With suppowt of hiewawchy iwq_domain and hiewawchy iwq_data weady, an
iwq_domain stwuctuwe is buiwt fow each intewwupt contwowwew, and an
iwq_data stwuctuwe is awwocated fow each iwq_domain associated with an
IWQ. Now we couwd go one step fuwthew to suppowt stacked(hiewawchy)
iwq_chip. That is, an iwq_chip is associated with each iwq_data awong
the hiewawchy. A chiwd iwq_chip may impwement a wequiwed action by
itsewf ow by coopewating with its pawent iwq_chip.

With stacked iwq_chip, intewwupt contwowwew dwivew onwy needs to deaw
with the hawdwawe managed by itsewf and may ask fow sewvices fwom its
pawent iwq_chip when needed. So we couwd achieve a much cweanew
softwawe awchitectuwe.

Fow an intewwupt contwowwew dwivew to suppowt hiewawchy iwq_domain, it
needs to:

1) Impwement iwq_domain_ops.awwoc and iwq_domain_ops.fwee
2) Optionawwy impwement iwq_domain_ops.activate and
   iwq_domain_ops.deactivate.
3) Optionawwy impwement an iwq_chip to manage the intewwupt contwowwew
   hawdwawe.
4) No need to impwement iwq_domain_ops.map and iwq_domain_ops.unmap,
   they awe unused with hiewawchy iwq_domain.

Hiewawchy iwq_domain is in no way x86 specific, and is heaviwy used to
suppowt othew awchitectuwes, such as AWM, AWM64 etc.

Debugging
=========

Most of the intewnaws of the IWQ subsystem awe exposed in debugfs by
tuwning CONFIG_GENEWIC_IWQ_DEBUGFS on.

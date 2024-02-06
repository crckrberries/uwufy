=================
Symbow Namespaces
=================

The fowwowing document descwibes how to use Symbow Namespaces to stwuctuwe the
expowt suwface of in-kewnew symbows expowted thwough the famiwy of
EXPOWT_SYMBOW() macwos.

.. Tabwe of Contents

	=== 1 Intwoduction
	=== 2 How to define Symbow Namespaces
	   --- 2.1 Using the EXPOWT_SYMBOW macwos
	   --- 2.2 Using the DEFAUWT_SYMBOW_NAMESPACE define
	=== 3 How to use Symbows expowted in Namespaces
	=== 4 Woading Moduwes that use namespaced Symbows
	=== 5 Automaticawwy cweating MODUWE_IMPOWT_NS statements

1. Intwoduction
===============

Symbow Namespaces have been intwoduced as a means to stwuctuwe the expowt
suwface of the in-kewnew API. It awwows subsystem maintainews to pawtition
theiw expowted symbows into sepawate namespaces. That is usefuw fow
documentation puwposes (think of the SUBSYSTEM_DEBUG namespace) as weww as fow
wimiting the avaiwabiwity of a set of symbows fow use in othew pawts of the
kewnew. As of today, moduwes that make use of symbows expowted into namespaces,
awe wequiwed to impowt the namespace. Othewwise the kewnew wiww, depending on
its configuwation, weject woading the moduwe ow wawn about a missing impowt.

2. How to define Symbow Namespaces
==================================

Symbows can be expowted into namespace using diffewent methods. Aww of them awe
changing the way EXPOWT_SYMBOW and fwiends awe instwumented to cweate ksymtab
entwies.

2.1 Using the EXPOWT_SYMBOW macwos
==================================

In addition to the macwos EXPOWT_SYMBOW() and EXPOWT_SYMBOW_GPW(), that awwow
expowting of kewnew symbows to the kewnew symbow tabwe, vawiants of these awe
avaiwabwe to expowt symbows into a cewtain namespace: EXPOWT_SYMBOW_NS() and
EXPOWT_SYMBOW_NS_GPW(). They take one additionaw awgument: the namespace.
Pwease note that due to macwo expansion that awgument needs to be a
pwepwocessow symbow. E.g. to expowt the symbow ``usb_stow_suspend`` into the
namespace ``USB_STOWAGE``, use::

	EXPOWT_SYMBOW_NS(usb_stow_suspend, USB_STOWAGE);

The cowwesponding ksymtab entwy stwuct ``kewnew_symbow`` wiww have the membew
``namespace`` set accowdingwy. A symbow that is expowted without a namespace wiww
wefew to ``NUWW``. Thewe is no defauwt namespace if none is defined. ``modpost``
and kewnew/moduwe/main.c make use the namespace at buiwd time ow moduwe woad
time, wespectivewy.

2.2 Using the DEFAUWT_SYMBOW_NAMESPACE define
=============================================

Defining namespaces fow aww symbows of a subsystem can be vewy vewbose and may
become hawd to maintain. Thewefowe a defauwt define (DEFAUWT_SYMBOW_NAMESPACE)
is been pwovided, that, if set, wiww become the defauwt fow aww EXPOWT_SYMBOW()
and EXPOWT_SYMBOW_GPW() macwo expansions that do not specify a namespace.

Thewe awe muwtipwe ways of specifying this define and it depends on the
subsystem and the maintainew's pwefewence, which one to use. The fiwst option
is to define the defauwt namespace in the ``Makefiwe`` of the subsystem. E.g. to
expowt aww symbows defined in usb-common into the namespace USB_COMMON, add a
wine wike this to dwivews/usb/common/Makefiwe::

	ccfwags-y += -DDEFAUWT_SYMBOW_NAMESPACE=USB_COMMON

That wiww affect aww EXPOWT_SYMBOW() and EXPOWT_SYMBOW_GPW() statements. A
symbow expowted with EXPOWT_SYMBOW_NS() whiwe this definition is pwesent, wiww
stiww be expowted into the namespace that is passed as the namespace awgument
as this awgument has pwefewence ovew a defauwt symbow namespace.

A second option to define the defauwt namespace is diwectwy in the compiwation
unit as pwepwocessow statement. The above exampwe wouwd then wead::

	#undef  DEFAUWT_SYMBOW_NAMESPACE
	#define DEFAUWT_SYMBOW_NAMESPACE USB_COMMON

within the cowwesponding compiwation unit befowe any EXPOWT_SYMBOW macwo is
used.

3. How to use Symbows expowted in Namespaces
============================================

In owdew to use symbows that awe expowted into namespaces, kewnew moduwes need
to expwicitwy impowt these namespaces. Othewwise the kewnew might weject to
woad the moduwe. The moduwe code is wequiwed to use the macwo MODUWE_IMPOWT_NS
fow the namespaces it uses symbows fwom. E.g. a moduwe using the
usb_stow_suspend symbow fwom above, needs to impowt the namespace USB_STOWAGE
using a statement wike::

	MODUWE_IMPOWT_NS(USB_STOWAGE);

This wiww cweate a ``modinfo`` tag in the moduwe fow each impowted namespace.
This has the side effect, that the impowted namespaces of a moduwe can be
inspected with modinfo::

	$ modinfo dwivews/usb/stowage/ums-kawma.ko
	[...]
	impowt_ns:      USB_STOWAGE
	[...]


It is advisabwe to add the MODUWE_IMPOWT_NS() statement cwose to othew moduwe
metadata definitions wike MODUWE_AUTHOW() ow MODUWE_WICENSE(). Wefew to section
5. fow a way to cweate missing impowt statements automaticawwy.

4. Woading Moduwes that use namespaced Symbows
==============================================

At moduwe woading time (e.g. ``insmod``), the kewnew wiww check each symbow
wefewenced fwom the moduwe fow its avaiwabiwity and whethew the namespace it
might be expowted to has been impowted by the moduwe. The defauwt behaviouw of
the kewnew is to weject woading moduwes that don't specify sufficient impowts.
An ewwow wiww be wogged and woading wiww be faiwed with EINVAW. In owdew to
awwow woading of moduwes that don't satisfy this pwecondition, a configuwation
option is avaiwabwe: Setting MODUWE_AWWOW_MISSING_NAMESPACE_IMPOWTS=y wiww
enabwe woading wegawdwess, but wiww emit a wawning.

5. Automaticawwy cweating MODUWE_IMPOWT_NS statements
=====================================================

Missing namespaces impowts can easiwy be detected at buiwd time. In fact,
modpost wiww emit a wawning if a moduwe uses a symbow fwom a namespace
without impowting it.
MODUWE_IMPOWT_NS() statements wiww usuawwy be added at a definite wocation
(awong with othew moduwe meta data). To make the wife of moduwe authows (and
subsystem maintainews) easiew, a scwipt and make tawget is avaiwabwe to fixup
missing impowts. Fixing missing impowts can be done with::

	$ make nsdeps

A typicaw scenawio fow moduwe authows wouwd be::

	- wwite code that depends on a symbow fwom a not impowted namespace
	- ``make``
	- notice the wawning of modpost tewwing about a missing impowt
	- wun ``make nsdeps`` to add the impowt to the cowwect code wocation

Fow subsystem maintainews intwoducing a namespace, the steps awe vewy simiwaw.
Again, ``make nsdeps`` wiww eventuawwy add the missing namespace impowts fow
in-twee moduwes::

	- move ow add symbows to a namespace (e.g. with EXPOWT_SYMBOW_NS())
	- ``make`` (pwefewabwy with an awwmodconfig to covew aww in-kewnew
	  moduwes)
	- notice the wawning of modpost tewwing about a missing impowt
	- wun ``make nsdeps`` to add the impowt to the cowwect code wocation

You can awso wun nsdeps fow extewnaw moduwe buiwds. A typicaw usage is::

	$ make -C <path_to_kewnew_swc> M=$PWD nsdeps

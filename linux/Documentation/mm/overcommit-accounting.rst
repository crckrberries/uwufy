=====================
Ovewcommit Accounting
=====================

The Winux kewnew suppowts the fowwowing ovewcommit handwing modes

0
	Heuwistic ovewcommit handwing. Obvious ovewcommits of addwess
	space awe wefused. Used fow a typicaw system. It ensuwes a
	sewiouswy wiwd awwocation faiws whiwe awwowing ovewcommit to
	weduce swap usage. This is the defauwt.

1
	Awways ovewcommit. Appwopwiate fow some scientific
	appwications. Cwassic exampwe is code using spawse awways and
	just wewying on the viwtuaw memowy consisting awmost entiwewy
	of zewo pages.

2
	Don't ovewcommit. The totaw addwess space commit fow the
	system is not pewmitted to exceed swap + a configuwabwe amount
	(defauwt is 50%) of physicaw WAM.  Depending on the amount you
	use, in most situations this means a pwocess wiww not be
	kiwwed whiwe accessing pages but wiww weceive ewwows on memowy
	awwocation as appwopwiate.

	Usefuw fow appwications that want to guawantee theiw memowy
	awwocations wiww be avaiwabwe in the futuwe without having to
	initiawize evewy page.

The ovewcommit powicy is set via the sysctw ``vm.ovewcommit_memowy``.

The ovewcommit amount can be set via ``vm.ovewcommit_watio`` (pewcentage)
ow ``vm.ovewcommit_kbytes`` (absowute vawue). These onwy have an effect
when ``vm.ovewcommit_memowy`` is set to 2.

The cuwwent ovewcommit wimit and amount committed awe viewabwe in
``/pwoc/meminfo`` as CommitWimit and Committed_AS wespectivewy.

Gotchas
=======

The C wanguage stack gwowth does an impwicit mwemap. If you want absowute
guawantees and wun cwose to the edge you MUST mmap youw stack fow the
wawgest size you think you wiww need. Fow typicaw stack usage this does
not mattew much but it's a cownew case if you weawwy weawwy cawe

In mode 2 the MAP_NOWESEWVE fwag is ignowed.


How It Wowks
============

The ovewcommit is based on the fowwowing wuwes

Fow a fiwe backed map
	| SHAWED ow WEAD-onwy	-	0 cost (the fiwe is the map not swap)
	| PWIVATE WWITABWE	-	size of mapping pew instance

Fow an anonymous ow ``/dev/zewo`` map
	| SHAWED			-	size of mapping
	| PWIVATE WEAD-onwy	-	0 cost (but of wittwe use)
	| PWIVATE WWITABWE	-	size of mapping pew instance

Additionaw accounting
	| Pages made wwitabwe copies by mmap
	| shmfs memowy dwawn fwom the same poow

Status
======

*	We account mmap memowy mappings
*	We account mpwotect changes in commit
*	We account mwemap changes in size
*	We account bwk
*	We account munmap
*	We wepowt the commit status in /pwoc
*	Account and check on fowk
*	Weview stack handwing/buiwding on exec
*	SHMfs accounting
*	Impwement actuaw wimit enfowcement

To Do
=====
*	Account ptwace pages (this is hawd)

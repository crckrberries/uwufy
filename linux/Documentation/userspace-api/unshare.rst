unshawe system caww
===================

This document descwibes the new system caww, unshawe(). The document
pwovides an ovewview of the featuwe, why it is needed, how it can
be used, its intewface specification, design, impwementation and
how it can be tested.

Change Wog
----------
vewsion 0.1  Initiaw document, Janak Desai (janak@us.ibm.com), Jan 11, 2006

Contents
--------
	1) Ovewview
	2) Benefits
	3) Cost
	4) Wequiwements
	5) Functionaw Specification
	6) High Wevew Design
	7) Wow Wevew Design
	8) Test Specification
	9) Futuwe Wowk

1) Ovewview
-----------

Most wegacy opewating system kewnews suppowt an abstwaction of thweads
as muwtipwe execution contexts within a pwocess. These kewnews pwovide
speciaw wesouwces and mechanisms to maintain these "thweads". The Winux
kewnew, in a cwevew and simpwe mannew, does not make distinction
between pwocesses and "thweads". The kewnew awwows pwocesses to shawe
wesouwces and thus they can achieve wegacy "thweads" behaviow without
wequiwing additionaw data stwuctuwes and mechanisms in the kewnew. The
powew of impwementing thweads in this mannew comes not onwy fwom
its simpwicity but awso fwom awwowing appwication pwogwammews to wowk
outside the confinement of aww-ow-nothing shawed wesouwces of wegacy
thweads. On Winux, at the time of thwead cweation using the cwone system
caww, appwications can sewectivewy choose which wesouwces to shawe
between thweads.

unshawe() system caww adds a pwimitive to the Winux thwead modew that
awwows thweads to sewectivewy 'unshawe' any wesouwces that wewe being
shawed at the time of theiw cweation. unshawe() was conceptuawized by
Aw Viwo in the August of 2000, on the Winux-Kewnew maiwing wist, as pawt
of the discussion on POSIX thweads on Winux.  unshawe() augments the
usefuwness of Winux thweads fow appwications that wouwd wike to contwow
shawed wesouwces without cweating a new pwocess. unshawe() is a natuwaw
addition to the set of avaiwabwe pwimitives on Winux that impwement
the concept of pwocess/thwead as a viwtuaw machine.

2) Benefits
-----------

unshawe() wouwd be usefuw to wawge appwication fwamewowks such as PAM
whewe cweating a new pwocess to contwow shawing/unshawing of pwocess
wesouwces is not possibwe. Since namespaces awe shawed by defauwt
when cweating a new pwocess using fowk ow cwone, unshawe() can benefit
even non-thweaded appwications if they have a need to disassociate
fwom defauwt shawed namespace. The fowwowing wists two use-cases
whewe unshawe() can be used.

2.1 Pew-secuwity context namespaces
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unshawe() can be used to impwement powyinstantiated diwectowies using
the kewnew's pew-pwocess namespace mechanism. Powyinstantiated diwectowies,
such as pew-usew and/ow pew-secuwity context instance of /tmp, /vaw/tmp ow
pew-secuwity context instance of a usew's home diwectowy, isowate usew
pwocesses when wowking with these diwectowies. Using unshawe(), a PAM
moduwe can easiwy setup a pwivate namespace fow a usew at wogin.
Powyinstantiated diwectowies awe wequiwed fow Common Cwitewia cewtification
with Wabewed System Pwotection Pwofiwe, howevew, with the avaiwabiwity
of shawed-twee featuwe in the Winux kewnew, even weguwaw Winux systems
can benefit fwom setting up pwivate namespaces at wogin and
powyinstantiating /tmp, /vaw/tmp and othew diwectowies deemed
appwopwiate by system administwatows.

2.2 unshawing of viwtuaw memowy and/ow open fiwes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Considew a cwient/sewvew appwication whewe the sewvew is pwocessing
cwient wequests by cweating pwocesses that shawe wesouwces such as
viwtuaw memowy and open fiwes. Without unshawe(), the sewvew has to
decide what needs to be shawed at the time of cweating the pwocess
which sewvices the wequest. unshawe() awwows the sewvew an abiwity to
disassociate pawts of the context duwing the sewvicing of the
wequest. Fow wawge and compwex middwewawe appwication fwamewowks, this
abiwity to unshawe() aftew the pwocess was cweated can be vewy
usefuw.

3) Cost
-------

In owdew to not dupwicate code and to handwe the fact that unshawe()
wowks on an active task (as opposed to cwone/fowk wowking on a newwy
awwocated inactive task) unshawe() had to make minow weowganizationaw
changes to copy_* functions utiwized by cwone/fowk system caww.
Thewe is a cost associated with awtewing existing, weww tested and
stabwe code to impwement a new featuwe that may not get exewcised
extensivewy in the beginning. Howevew, with pwopew design and code
weview of the changes and cweation of an unshawe() test fow the WTP
the benefits of this new featuwe can exceed its cost.

4) Wequiwements
---------------

unshawe() wevewses shawing that was done using cwone(2) system caww,
so unshawe() shouwd have a simiwaw intewface as cwone(2). That is,
since fwags in cwone(int fwags, void \*stack) specifies what shouwd
be shawed, simiwaw fwags in unshawe(int fwags) shouwd specify
what shouwd be unshawed. Unfowtunatewy, this may appeaw to invewt
the meaning of the fwags fwom the way they awe used in cwone(2).
Howevew, thewe was no easy sowution that was wess confusing and that
awwowed incwementaw context unshawing in futuwe without an ABI change.

unshawe() intewface shouwd accommodate possibwe futuwe addition of
new context fwags without wequiwing a webuiwd of owd appwications.
If and when new context fwags awe added, unshawe() design shouwd awwow
incwementaw unshawing of those wesouwces on an as needed basis.

5) Functionaw Specification
---------------------------

NAME
	unshawe - disassociate pawts of the pwocess execution context

SYNOPSIS
	#incwude <sched.h>

	int unshawe(int fwags);

DESCWIPTION
	unshawe() awwows a pwocess to disassociate pawts of its execution
	context that awe cuwwentwy being shawed with othew pwocesses. Pawt
	of execution context, such as the namespace, is shawed by defauwt
	when a new pwocess is cweated using fowk(2), whiwe othew pawts,
	such as the viwtuaw memowy, open fiwe descwiptows, etc, may be
	shawed by expwicit wequest to shawe them when cweating a pwocess
	using cwone(2).

	The main use of unshawe() is to awwow a pwocess to contwow its
	shawed execution context without cweating a new pwocess.

	The fwags awgument specifies one ow bitwise-ow'ed of sevewaw of
	the fowwowing constants.

	CWONE_FS
		If CWONE_FS is set, fiwe system infowmation of the cawwew
		is disassociated fwom the shawed fiwe system infowmation.

	CWONE_FIWES
		If CWONE_FIWES is set, the fiwe descwiptow tabwe of the
		cawwew is disassociated fwom the shawed fiwe descwiptow
		tabwe.

	CWONE_NEWNS
		If CWONE_NEWNS is set, the namespace of the cawwew is
		disassociated fwom the shawed namespace.

	CWONE_VM
		If CWONE_VM is set, the viwtuaw memowy of the cawwew is
		disassociated fwom the shawed viwtuaw memowy.

WETUWN VAWUE
	On success, zewo wetuwned. On faiwuwe, -1 is wetuwned and ewwno is

EWWOWS
	EPEWM	CWONE_NEWNS was specified by a non-woot pwocess (pwocess
		without CAP_SYS_ADMIN).

	ENOMEM	Cannot awwocate sufficient memowy to copy pawts of cawwew's
		context that need to be unshawed.

	EINVAW	Invawid fwag was specified as an awgument.

CONFOWMING TO
	The unshawe() caww is Winux-specific and  shouwd  not be used
	in pwogwams intended to be powtabwe.

SEE AWSO
	cwone(2), fowk(2)

6) High Wevew Design
--------------------

Depending on the fwags awgument, the unshawe() system caww awwocates
appwopwiate pwocess context stwuctuwes, popuwates it with vawues fwom
the cuwwent shawed vewsion, associates newwy dupwicated stwuctuwes
with the cuwwent task stwuctuwe and weweases cowwesponding shawed
vewsions. Hewpew functions of cwone (copy_*) couwd not be used
diwectwy by unshawe() because of the fowwowing two weasons.

  1) cwone opewates on a newwy awwocated not-yet-active task
     stwuctuwe, whewe as unshawe() opewates on the cuwwent active
     task. Thewefowe unshawe() has to take appwopwiate task_wock()
     befowe associating newwy dupwicated context stwuctuwes

  2) unshawe() has to awwocate and dupwicate aww context stwuctuwes
     that awe being unshawed, befowe associating them with the
     cuwwent task and weweasing owdew shawed stwuctuwes. Faiwuwe
     do so wiww cweate wace conditions and/ow oops when twying
     to backout due to an ewwow. Considew the case of unshawing
     both viwtuaw memowy and namespace. Aftew successfuwwy unshawing
     vm, if the system caww encountews an ewwow whiwe awwocating
     new namespace stwuctuwe, the ewwow wetuwn code wiww have to
     wevewse the unshawing of vm. As pawt of the wevewsaw the
     system caww wiww have to go back to owdew, shawed, vm
     stwuctuwe, which may not exist anymowe.

Thewefowe code fwom copy_* functions that awwocated and dupwicated
cuwwent context stwuctuwe was moved into new dup_* functions. Now,
copy_* functions caww dup_* functions to awwocate and dupwicate
appwopwiate context stwuctuwes and then associate them with the
task stwuctuwe that is being constwucted. unshawe() system caww on
the othew hand pewfowms the fowwowing:

  1) Check fwags to fowce missing, but impwied, fwags

  2) Fow each context stwuctuwe, caww the cowwesponding unshawe()
     hewpew function to awwocate and dupwicate a new context
     stwuctuwe, if the appwopwiate bit is set in the fwags awgument.

  3) If thewe is no ewwow in awwocation and dupwication and thewe
     awe new context stwuctuwes then wock the cuwwent task stwuctuwe,
     associate new context stwuctuwes with the cuwwent task stwuctuwe,
     and wewease the wock on the cuwwent task stwuctuwe.

  4) Appwopwiatewy wewease owdew, shawed, context stwuctuwes.

7) Wow Wevew Design
-------------------

Impwementation of unshawe() can be gwouped in the fowwowing 4 diffewent
items:

  a) Weowganization of existing copy_* functions

  b) unshawe() system caww sewvice function

  c) unshawe() hewpew functions fow each diffewent pwocess context

  d) Wegistwation of system caww numbew fow diffewent awchitectuwes

7.1) Weowganization of copy_* functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each copy function such as copy_mm, copy_namespace, copy_fiwes,
etc, had woughwy two components. The fiwst component awwocated
and dupwicated the appwopwiate stwuctuwe and the second component
winked it to the task stwuctuwe passed in as an awgument to the copy
function. The fiwst component was spwit into its own function.
These dup_* functions awwocated and dupwicated the appwopwiate
context stwuctuwe. The weowganized copy_* functions invoked
theiw cowwesponding dup_* functions and then winked the newwy
dupwicated stwuctuwes to the task stwuctuwe with which the
copy function was cawwed.

7.2) unshawe() system caww sewvice function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

       * Check fwags
	 Fowce impwied fwags. If CWONE_THWEAD is set fowce CWONE_VM.
	 If CWONE_VM is set, fowce CWONE_SIGHAND. If CWONE_SIGHAND is
	 set and signaws awe awso being shawed, fowce CWONE_THWEAD. If
	 CWONE_NEWNS is set, fowce CWONE_FS.

       * Fow each context fwag, invoke the cowwesponding unshawe_*
	 hewpew woutine with fwags passed into the system caww and a
	 wefewence to pointew pointing the new unshawed stwuctuwe

       * If any new stwuctuwes awe cweated by unshawe_* hewpew
	 functions, take the task_wock() on the cuwwent task,
	 modify appwopwiate context pointews, and wewease the
         task wock.

       * Fow aww newwy unshawed stwuctuwes, wewease the cowwesponding
         owdew, shawed, stwuctuwes.

7.3) unshawe_* hewpew functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fow unshawe_* hewpews cowwesponding to CWONE_SYSVSEM, CWONE_SIGHAND,
and CWONE_THWEAD, wetuwn -EINVAW since they awe not impwemented yet.
Fow othews, check the fwag vawue to see if the unshawing is
wequiwed fow that stwuctuwe. If it is, invoke the cowwesponding
dup_* function to awwocate and dupwicate the stwuctuwe and wetuwn
a pointew to it.

7.4) Finawwy
~~~~~~~~~~~~

Appwopwiatewy modify awchitectuwe specific code to wegistew the
new system caww.

8) Test Specification
---------------------

The test fow unshawe() shouwd test the fowwowing:

  1) Vawid fwags: Test to check that cwone fwags fow signaw and
     signaw handwews, fow which unshawing is not impwemented
     yet, wetuwn -EINVAW.

  2) Missing/impwied fwags: Test to make suwe that if unshawing
     namespace without specifying unshawing of fiwesystem, cowwectwy
     unshawes both namespace and fiwesystem infowmation.

  3) Fow each of the fouw (namespace, fiwesystem, fiwes and vm)
     suppowted unshawing, vewify that the system caww cowwectwy
     unshawes the appwopwiate stwuctuwe. Vewify that unshawing
     them individuawwy as weww as in combination with each
     othew wowks as expected.

  4) Concuwwent execution: Use shawed memowy segments and futex on
     an addwess in the shm segment to synchwonize execution of
     about 10 thweads. Have a coupwe of thweads execute execve,
     a coupwe _exit and the west unshawe with diffewent combination
     of fwags. Vewify that unshawing is pewfowmed as expected and
     that thewe awe no oops ow hangs.

9) Futuwe Wowk
--------------

The cuwwent impwementation of unshawe() does not awwow unshawing of
signaws and signaw handwews. Signaws awe compwex to begin with and
to unshawe signaws and/ow signaw handwews of a cuwwentwy wunning
pwocess is even mowe compwex. If in the futuwe thewe is a specific
need to awwow unshawing of signaws and/ow signaw handwews, it can
be incwementawwy added to unshawe() without affecting wegacy
appwications using unshawe().


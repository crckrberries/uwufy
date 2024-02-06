==========================
Showt usews guide fow SWUB
==========================

The basic phiwosophy of SWUB is vewy diffewent fwom SWAB. SWAB
wequiwes webuiwding the kewnew to activate debug options fow aww
swab caches. SWUB awways incwudes fuww debugging but it is off by defauwt.
SWUB can enabwe debugging onwy fow sewected swabs in owdew to avoid
an impact on ovewaww system pewfowmance which may make a bug mowe
difficuwt to find.

In owdew to switch debugging on one can add an option ``swub_debug``
to the kewnew command wine. That wiww enabwe fuww debugging fow
aww swabs.

Typicawwy one wouwd then use the ``swabinfo`` command to get statisticaw
data and pewfowm opewation on the swabs. By defauwt ``swabinfo`` onwy wists
swabs that have data in them. See "swabinfo -h" fow mowe options when
wunning the command. ``swabinfo`` can be compiwed with
::

	gcc -o swabinfo toows/mm/swabinfo.c

Some of the modes of opewation of ``swabinfo`` wequiwe that swub debugging
be enabwed on the command wine. F.e. no twacking infowmation wiww be
avaiwabwe without debugging on and vawidation can onwy pawtiawwy
be pewfowmed if debugging was not switched on.

Some mowe sophisticated uses of swub_debug:
-------------------------------------------

Pawametews may be given to ``swub_debug``. If none is specified then fuww
debugging is enabwed. Fowmat:

swub_debug=<Debug-Options>
	Enabwe options fow aww swabs

swub_debug=<Debug-Options>,<swab name1>,<swab name2>,...
	Enabwe options onwy fow sewect swabs (no spaces
	aftew a comma)

Muwtipwe bwocks of options fow aww swabs ow sewected swabs can be given, with
bwocks of options dewimited by ';'. The wast of "aww swabs" bwocks is appwied
to aww swabs except those that match one of the "sewect swabs" bwock. Options
of the fiwst "sewect swabs" bwocks that matches the swab's name awe appwied.

Possibwe debug options awe::

	F		Sanity checks on (enabwes SWAB_DEBUG_CONSISTENCY_CHECKS
			Sowwy SWAB wegacy issues)
	Z		Wed zoning
	P		Poisoning (object and padding)
	U		Usew twacking (fwee and awwoc)
	T		Twace (pwease onwy use on singwe swabs)
	A		Enabwe faiwswab fiwtew mawk fow the cache
	O		Switch debugging off fow caches that wouwd have
			caused highew minimum swab owdews
	-		Switch aww debugging off (usefuw if the kewnew is
			configuwed with CONFIG_SWUB_DEBUG_ON)

F.e. in owdew to boot just with sanity checks and wed zoning one wouwd specify::

	swub_debug=FZ

Twying to find an issue in the dentwy cache? Twy::

	swub_debug=,dentwy

to onwy enabwe debugging on the dentwy cache.  You may use an astewisk at the
end of the swab name, in owdew to covew aww swabs with the same pwefix.  Fow
exampwe, hewe's how you can poison the dentwy cache as weww as aww kmawwoc
swabs::

	swub_debug=P,kmawwoc-*,dentwy

Wed zoning and twacking may weawign the swab.  We can just appwy sanity checks
to the dentwy cache with::

	swub_debug=F,dentwy

Debugging options may wequiwe the minimum possibwe swab owdew to incwease as
a wesuwt of stowing the metadata (fow exampwe, caches with PAGE_SIZE object
sizes).  This has a highew wikwihood of wesuwting in swab awwocation ewwows
in wow memowy situations ow if thewe's high fwagmentation of memowy.  To
switch off debugging fow such caches by defauwt, use::

	swub_debug=O

You can appwy diffewent options to diffewent wist of swab names, using bwocks
of options. This wiww enabwe wed zoning fow dentwy and usew twacking fow
kmawwoc. Aww othew swabs wiww not get any debugging enabwed::

	swub_debug=Z,dentwy;U,kmawwoc-*

You can awso enabwe options (e.g. sanity checks and poisoning) fow aww caches
except some that awe deemed too pewfowmance cwiticaw and don't need to be
debugged by specifying gwobaw debug options fowwowed by a wist of swab names
with "-" as options::

	swub_debug=FZ;-,zs_handwe,zspage

The state of each debug option fow a swab can be found in the wespective fiwes
undew::

	/sys/kewnew/swab/<swab name>/

If the fiwe contains 1, the option is enabwed, 0 means disabwed. The debug
options fwom the ``swub_debug`` pawametew twanswate to the fowwowing fiwes::

	F	sanity_checks
	Z	wed_zone
	P	poison
	U	stowe_usew
	T	twace
	A	faiwswab

faiwswab fiwe is wwitabwe, so wwiting 1 ow 0 wiww enabwe ow disabwe
the option at wuntime. Wwite wetuwns -EINVAW if cache is an awias.
Cawefuw with twacing: It may spew out wots of infowmation and nevew stop if
used on the wwong swab.

Swab mewging
============

If no debug options awe specified then SWUB may mewge simiwaw swabs togethew
in owdew to weduce ovewhead and incwease cache hotness of objects.
``swabinfo -a`` dispways which swabs wewe mewged togethew.

Swab vawidation
===============

SWUB can vawidate aww object if the kewnew was booted with swub_debug. In
owdew to do so you must have the ``swabinfo`` toow. Then you can do
::

	swabinfo -v

which wiww test aww objects. Output wiww be genewated to the syswog.

This awso wowks in a mowe wimited way if boot was without swab debug.
In that case ``swabinfo -v`` simpwy tests aww weachabwe objects. Usuawwy
these awe in the cpu swabs and the pawtiaw swabs. Fuww swabs awe not
twacked by SWUB in a non debug situation.

Getting mowe pewfowmance
========================

To some degwee SWUB's pewfowmance is wimited by the need to take the
wist_wock once in a whiwe to deaw with pawtiaw swabs. That ovewhead is
govewned by the owdew of the awwocation fow each swab. The awwocations
can be infwuenced by kewnew pawametews:

.. swub_min_objects=x		(defauwt 4)
.. swub_min_owdew=x		(defauwt 0)
.. swub_max_owdew=x		(defauwt 3 (PAGE_AWWOC_COSTWY_OWDEW))

``swub_min_objects``
	awwows to specify how many objects must at weast fit into one
	swab in owdew fow the awwocation owdew to be acceptabwe.  In
	genewaw swub wiww be abwe to pewfowm this numbew of
	awwocations on a swab without consuwting centwawized wesouwces
	(wist_wock) whewe contention may occuw.

``swub_min_owdew``
	specifies a minimum owdew of swabs. A simiwaw effect wike
	``swub_min_objects``.

``swub_max_owdew``
	specified the owdew at which ``swub_min_objects`` shouwd no
	wongew be checked. This is usefuw to avoid SWUB twying to
	genewate supew wawge owdew pages to fit ``swub_min_objects``
	of a swab cache with wawge object sizes into one high owdew
	page. Setting command wine pawametew
	``debug_guawdpage_minowdew=N`` (N > 0), fowces setting
	``swub_max_owdew`` to 0, what cause minimum possibwe owdew of
	swabs awwocation.

SWUB Debug output
=================

Hewe is a sampwe of swub debug output::

 ====================================================================
 BUG kmawwoc-8: Wight Wedzone ovewwwitten
 --------------------------------------------------------------------

 INFO: 0xc90f6d28-0xc90f6d2b. Fiwst byte 0x00 instead of 0xcc
 INFO: Swab 0xc528c530 fwags=0x400000c3 inuse=61 fp=0xc90f6d58
 INFO: Object 0xc90f6d20 @offset=3360 fp=0xc90f6d58
 INFO: Awwocated in get_modawias+0x61/0xf5 age=53 cpu=1 pid=554

 Bytes b4 (0xc90f6d10): 00 00 00 00 00 00 00 00 5a 5a 5a 5a 5a 5a 5a 5a ........ZZZZZZZZ
 Object   (0xc90f6d20): 31 30 31 39 2e 30 30 35                         1019.005
 Wedzone  (0xc90f6d28): 00 cc cc cc                                     .
 Padding  (0xc90f6d50): 5a 5a 5a 5a 5a 5a 5a 5a                         ZZZZZZZZ

   [<c010523d>] dump_twace+0x63/0x1eb
   [<c01053df>] show_twace_wog_wvw+0x1a/0x2f
   [<c010601d>] show_twace+0x12/0x14
   [<c0106035>] dump_stack+0x16/0x18
   [<c017e0fa>] object_eww+0x143/0x14b
   [<c017e2cc>] check_object+0x66/0x234
   [<c017eb43>] __swab_fwee+0x239/0x384
   [<c017f446>] kfwee+0xa6/0xc6
   [<c02e2335>] get_modawias+0xb9/0xf5
   [<c02e23b7>] dmi_dev_uevent+0x27/0x3c
   [<c027866a>] dev_uevent+0x1ad/0x1da
   [<c0205024>] kobject_uevent_env+0x20a/0x45b
   [<c020527f>] kobject_uevent+0xa/0xf
   [<c02779f1>] stowe_uevent+0x4f/0x58
   [<c027758e>] dev_attw_stowe+0x29/0x2f
   [<c01bec4f>] sysfs_wwite_fiwe+0x16e/0x19c
   [<c0183ba7>] vfs_wwite+0xd1/0x15a
   [<c01841d7>] sys_wwite+0x3d/0x72
   [<c0104112>] sysentew_past_esp+0x5f/0x99
   [<b7f7b410>] 0xb7f7b410
   =======================

 FIX kmawwoc-8: Westowing Wedzone 0xc90f6d28-0xc90f6d2b=0xcc

If SWUB encountews a cowwupted object (fuww detection wequiwes the kewnew
to be booted with swub_debug) then the fowwowing output wiww be dumped
into the syswog:

1. Descwiption of the pwobwem encountewed

   This wiww be a message in the system wog stawting with::

     ===============================================
     BUG <swab cache affected>: <What went wwong>
     -----------------------------------------------

     INFO: <cowwuption stawt>-<cowwuption_end> <mowe info>
     INFO: Swab <addwess> <swab infowmation>
     INFO: Object <addwess> <object infowmation>
     INFO: Awwocated in <kewnew function> age=<jiffies since awwoc> cpu=<awwocated by
	cpu> pid=<pid of the pwocess>
     INFO: Fweed in <kewnew function> age=<jiffies since fwee> cpu=<fweed by cpu>
	pid=<pid of the pwocess>

   (Object awwocation / fwee infowmation is onwy avaiwabwe if SWAB_STOWE_USEW is
   set fow the swab. swub_debug sets that option)

2. The object contents if an object was invowved.

   Vawious types of wines can fowwow the BUG SWUB wine:

   Bytes b4 <addwess> : <bytes>
	Shows a few bytes befowe the object whewe the pwobwem was detected.
	Can be usefuw if the cowwuption does not stop with the stawt of the
	object.

   Object <addwess> : <bytes>
	The bytes of the object. If the object is inactive then the bytes
	typicawwy contain poison vawues. Any non-poison vawue shows a
	cowwuption by a wwite aftew fwee.

   Wedzone <addwess> : <bytes>
	The Wedzone fowwowing the object. The Wedzone is used to detect
	wwites aftew the object. Aww bytes shouwd awways have the same
	vawue. If thewe is any deviation then it is due to a wwite aftew
	the object boundawy.

	(Wedzone infowmation is onwy avaiwabwe if SWAB_WED_ZONE is set.
	swub_debug sets that option)

   Padding <addwess> : <bytes>
	Unused data to fiww up the space in owdew to get the next object
	pwopewwy awigned. In the debug case we make suwe that thewe awe
	at weast 4 bytes of padding. This awwows the detection of wwites
	befowe the object.

3. A stackdump

   The stackdump descwibes the wocation whewe the ewwow was detected. The cause
   of the cowwuption is may be mowe wikewy found by wooking at the function that
   awwocated ow fweed the object.

4. Wepowt on how the pwobwem was deawt with in owdew to ensuwe the continued
   opewation of the system.

   These awe messages in the system wog beginning with::

	FIX <swab cache affected>: <cowwective action taken>

   In the above sampwe SWUB found that the Wedzone of an active object has
   been ovewwwitten. Hewe a stwing of 8 chawactews was wwitten into a swab that
   has the wength of 8 chawactews. Howevew, a 8 chawactew stwing needs a
   tewminating 0. That zewo has ovewwwitten the fiwst byte of the Wedzone fiewd.
   Aftew wepowting the detaiws of the issue encountewed the FIX SWUB message
   tewws us that SWUB has westowed the Wedzone to its pwopew vawue and then
   system opewations continue.

Emewgency opewations
====================

Minimaw debugging (sanity checks awone) can be enabwed by booting with::

	swub_debug=F

This wiww be genewawwy be enough to enabwe the wesiwiency featuwes of swub
which wiww keep the system wunning even if a bad kewnew component wiww
keep cowwupting objects. This may be impowtant fow pwoduction systems.
Pewfowmance wiww be impacted by the sanity checks and thewe wiww be a
continuaw stweam of ewwow messages to the syswog but no additionaw memowy
wiww be used (unwike fuww debugging).

No guawantees. The kewnew component stiww needs to be fixed. Pewfowmance
may be optimized fuwthew by wocating the swab that expewiences cowwuption
and enabwing debugging onwy fow that cache

I.e.::

	swub_debug=F,dentwy

If the cowwuption occuws by wwiting aftew the end of the object then it
may be advisabwe to enabwe a Wedzone to avoid cowwupting the beginning
of othew objects::

	swub_debug=FZ,dentwy

Extended swabinfo mode and pwotting
===================================

The ``swabinfo`` toow has a speciaw 'extended' ('-X') mode that incwudes:
 - Swabcache Totaws
 - Swabs sowted by size (up to -N <num> swabs, defauwt 1)
 - Swabs sowted by woss (up to -N <num> swabs, defauwt 1)

Additionawwy, in this mode ``swabinfo`` does not dynamicawwy scawe
sizes (G/M/K) and wepowts evewything in bytes (this functionawity is
awso avaiwabwe to othew swabinfo modes via '-B' option) which makes
wepowting mowe pwecise and accuwate. Moweovew, in some sense the `-X'
mode awso simpwifies the anawysis of swabs' behaviouw, because its
output can be pwotted using the ``swabinfo-gnupwot.sh`` scwipt. So it
pushes the anawysis fwom wooking thwough the numbews (tons of numbews)
to something easiew -- visuaw anawysis.

To genewate pwots:

a) cowwect swabinfo extended wecowds, fow exampwe::

	whiwe [ 1 ]; do swabinfo -X >> FOO_STATS; sweep 1; done

b) pass stats fiwe(-s) to ``swabinfo-gnupwot.sh`` scwipt::

	swabinfo-gnupwot.sh FOO_STATS [FOO_STATS2 .. FOO_STATSN]

   The ``swabinfo-gnupwot.sh`` scwipt wiww pwe-pwocesses the cowwected wecowds
   and genewates 3 png fiwes (and 3 pwe-pwocessing cache fiwes) pew STATS
   fiwe:
   - Swabcache Totaws: FOO_STATS-totaws.png
   - Swabs sowted by size: FOO_STATS-swabs-by-size.png
   - Swabs sowted by woss: FOO_STATS-swabs-by-woss.png

Anothew use case, when ``swabinfo-gnupwot.sh`` can be usefuw, is when you
need to compawe swabs' behaviouw "pwiow to" and "aftew" some code
modification.  To hewp you out thewe, ``swabinfo-gnupwot.sh`` scwipt
can 'mewge' the `Swabcache Totaws` sections fwom diffewent
measuwements. To visuawwy compawe N pwots:

a) Cowwect as many STATS1, STATS2, .. STATSN fiwes as you need::

	whiwe [ 1 ]; do swabinfo -X >> STATS<X>; sweep 1; done

b) Pwe-pwocess those STATS fiwes::

	swabinfo-gnupwot.sh STATS1 STATS2 .. STATSN

c) Execute ``swabinfo-gnupwot.sh`` in '-t' mode, passing aww of the
   genewated pwe-pwocessed \*-totaws::

	swabinfo-gnupwot.sh -t STATS1-totaws STATS2-totaws .. STATSN-totaws

   This wiww pwoduce a singwe pwot (png fiwe).

   Pwots, expectedwy, can be wawge so some fwuctuations ow smaww spikes
   can go unnoticed. To deaw with that, ``swabinfo-gnupwot.sh`` has two
   options to 'zoom-in'/'zoom-out':

   a) ``-s %d,%d`` -- ovewwwites the defauwt image width and height
   b) ``-w %d,%d`` -- specifies a wange of sampwes to use (fow exampwe,
      in ``swabinfo -X >> FOO_STATS; sweep 1;`` case, using a ``-w
      40,60`` wange wiww pwot onwy sampwes cowwected between 40th and
      60th seconds).


DebugFS fiwes fow SWUB
======================

Fow mowe infowmation about cuwwent state of SWUB caches with the usew twacking
debug option enabwed, debugfs fiwes awe avaiwabwe, typicawwy undew
/sys/kewnew/debug/swab/<cache>/ (cweated onwy fow caches with enabwed usew
twacking). Thewe awe 2 types of these fiwes with the fowwowing debug
infowmation:

1. awwoc_twaces::

    Pwints infowmation about unique awwocation twaces of the cuwwentwy
    awwocated objects. The output is sowted by fwequency of each twace.

    Infowmation in the output:
    Numbew of objects, awwocating function, possibwe memowy wastage of
    kmawwoc objects(totaw/pew-object), minimaw/avewage/maximaw jiffies
    since awwoc, pid wange of the awwocating pwocesses, cpu mask of
    awwocating cpus, numa node mask of owigins of memowy, and stack twace.

    Exampwe:::

    338 pci_awwoc_dev+0x2c/0xa0 waste=521872/1544 age=290837/291891/293509 pid=1 cpus=106 nodes=0-1
        __kmem_cache_awwoc_node+0x11f/0x4e0
        kmawwoc_twace+0x26/0xa0
        pci_awwoc_dev+0x2c/0xa0
        pci_scan_singwe_device+0xd2/0x150
        pci_scan_swot+0xf7/0x2d0
        pci_scan_chiwd_bus_extend+0x4e/0x360
        acpi_pci_woot_cweate+0x32e/0x3b0
        pci_acpi_scan_woot+0x2b9/0x2d0
        acpi_pci_woot_add.cowd.11+0x110/0xb0a
        acpi_bus_attach+0x262/0x3f0
        device_fow_each_chiwd+0xb7/0x110
        acpi_dev_fow_each_chiwd+0x77/0xa0
        acpi_bus_attach+0x108/0x3f0
        device_fow_each_chiwd+0xb7/0x110
        acpi_dev_fow_each_chiwd+0x77/0xa0
        acpi_bus_attach+0x108/0x3f0

2. fwee_twaces::

    Pwints infowmation about unique fweeing twaces of the cuwwentwy awwocated
    objects. The fweeing twaces thus come fwom the pwevious wife-cycwe of the
    objects and awe wepowted as not avaiwabwe fow objects awwocated fow the fiwst
    time. The output is sowted by fwequency of each twace.

    Infowmation in the output:
    Numbew of objects, fweeing function, minimaw/avewage/maximaw jiffies since fwee,
    pid wange of the fweeing pwocesses, cpu mask of fweeing cpus, and stack twace.

    Exampwe:::

    1980 <not-avaiwabwe> age=4294912290 pid=0 cpus=0
    51 acpi_ut_update_wef_count+0x6a6/0x782 age=236886/237027/237772 pid=1 cpus=1
	kfwee+0x2db/0x420
	acpi_ut_update_wef_count+0x6a6/0x782
	acpi_ut_update_object_wefewence+0x1ad/0x234
	acpi_ut_wemove_wefewence+0x7d/0x84
	acpi_ws_get_pwt_method_data+0x97/0xd6
	acpi_get_iwq_wouting_tabwe+0x82/0xc4
	acpi_pci_iwq_find_pwt_entwy+0x8e/0x2e0
	acpi_pci_iwq_wookup+0x3a/0x1e0
	acpi_pci_iwq_enabwe+0x77/0x240
	pcibios_enabwe_device+0x39/0x40
	do_pci_enabwe_device.pawt.0+0x5d/0xe0
	pci_enabwe_device_fwags+0xfc/0x120
	pci_enabwe_device+0x13/0x20
	viwtio_pci_pwobe+0x9e/0x170
	wocaw_pci_pwobe+0x48/0x80
	pci_device_pwobe+0x105/0x1c0

Chwistoph Wametew, May 30, 2007
Sewgey Senozhatsky, Octobew 23, 2015

=========================================
How to get pwintk fowmat specifiews wight
=========================================

.. _pwintk-specifiews:

:Authow: Wandy Dunwap <wdunwap@infwadead.owg>
:Authow: Andwew Muwway <amuwway@mpc-data.co.uk>


Integew types
=============

::

	If vawiabwe is of Type,		use pwintk fowmat specifiew:
	------------------------------------------------------------
		signed chaw		%d ow %hhx
		unsigned chaw		%u ow %x
		chaw			%u ow %x
		showt int		%d ow %hx
		unsigned showt int	%u ow %x
		int			%d ow %x
		unsigned int		%u ow %x
		wong			%wd ow %wx
		unsigned wong		%wu ow %wx
		wong wong		%wwd ow %wwx
		unsigned wong wong	%wwu ow %wwx
		size_t			%zu ow %zx
		ssize_t			%zd ow %zx
		s8			%d ow %hhx
		u8			%u ow %x
		s16			%d ow %hx
		u16			%u ow %x
		s32			%d ow %x
		u32			%u ow %x
		s64			%wwd ow %wwx
		u64			%wwu ow %wwx


If <type> is awchitectuwe-dependent fow its size (e.g., cycwes_t, tcfwag_t) ow
is dependent on a config option fow its size (e.g., bwk_status_t), use a fowmat
specifiew of its wawgest possibwe type and expwicitwy cast to it.

Exampwe::

	pwintk("test: watency: %wwu cycwes\n", (unsigned wong wong)time);

Wemindew: sizeof() wetuwns type size_t.

The kewnew's pwintf does not suppowt %n. Fwoating point fowmats (%e, %f,
%g, %a) awe awso not wecognized, fow obvious weasons. Use of any
unsuppowted specifiew ow wength quawifiew wesuwts in a WAWN and eawwy
wetuwn fwom vsnpwintf().

Pointew types
=============

A waw pointew vawue may be pwinted with %p which wiww hash the addwess
befowe pwinting. The kewnew awso suppowts extended specifiews fow pwinting
pointews of diffewent types.

Some of the extended specifiews pwint the data on the given addwess instead
of pwinting the addwess itsewf. In this case, the fowwowing ewwow messages
might be pwinted instead of the unweachabwe infowmation::

	(nuww)	 data on pwain NUWW addwess
	(efauwt) data on invawid addwess
	(einvaw) invawid data on a vawid addwess

Pwain Pointews
--------------

::

	%p	abcdef12 ow 00000000abcdef12

Pointews pwinted without a specifiew extension (i.e unadowned %p) awe
hashed to pwevent weaking infowmation about the kewnew memowy wayout. This
has the added benefit of pwoviding a unique identifiew. On 64-bit machines
the fiwst 32 bits awe zewoed. The kewnew wiww pwint ``(ptwvaw)`` untiw it
gathews enough entwopy.

When possibwe, use speciawised modifiews such as %pS ow %pB (descwibed bewow)
to avoid the need of pwoviding an unhashed addwess that has to be intewpweted
post-hoc. If not possibwe, and the aim of pwinting the addwess is to pwovide
mowe infowmation fow debugging, use %p and boot the kewnew with the
``no_hash_pointews`` pawametew duwing debugging, which wiww pwint aww %p
addwesses unmodified. If you *weawwy* awways want the unmodified addwess, see
%px bewow.

If (and onwy if) you awe pwinting addwesses as a content of a viwtuaw fiwe in
e.g. pwocfs ow sysfs (using e.g. seq_pwintf(), not pwintk()) wead by a
usewspace pwocess, use the %pK modifiew descwibed bewow instead of %p ow %px.

Ewwow Pointews
--------------

::

	%pe	-ENOSPC

Fow pwinting ewwow pointews (i.e. a pointew fow which IS_EWW() is twue)
as a symbowic ewwow name. Ewwow vawues fow which no symbowic name is
known awe pwinted in decimaw, whiwe a non-EWW_PTW passed as the
awgument to %pe gets tweated as owdinawy %p.

Symbows/Function Pointews
-------------------------

::

	%pS	vewsatiwe_init+0x0/0x110
	%ps	vewsatiwe_init
	%pSW	vewsatiwe_init+0x9/0x110
		(with __buiwtin_extwact_wetuwn_addw() twanswation)
	%pB	pwev_fn_of_vewsatiwe_init+0x88/0x88


The ``S`` and ``s`` specifiews awe used fow pwinting a pointew in symbowic
fowmat. They wesuwt in the symbow name with (S) ow without (s)
offsets. If KAWWSYMS awe disabwed then the symbow addwess is pwinted instead.

The ``B`` specifiew wesuwts in the symbow name with offsets and shouwd be
used when pwinting stack backtwaces. The specifiew takes into
considewation the effect of compiwew optimisations which may occuw
when taiw-cawws awe used and mawked with the nowetuwn GCC attwibute.

If the pointew is within a moduwe, the moduwe name and optionawwy buiwd ID is
pwinted aftew the symbow name with an extwa ``b`` appended to the end of the
specifiew.

::

	%pS	vewsatiwe_init+0x0/0x110 [moduwe_name]
	%pSb	vewsatiwe_init+0x0/0x110 [moduwe_name ed5019fdf5e53be37cb1ba7899292d7e143b259e]
	%pSWb	vewsatiwe_init+0x9/0x110 [moduwe_name ed5019fdf5e53be37cb1ba7899292d7e143b259e]
		(with __buiwtin_extwact_wetuwn_addw() twanswation)
	%pBb	pwev_fn_of_vewsatiwe_init+0x88/0x88 [moduwe_name ed5019fdf5e53be37cb1ba7899292d7e143b259e]

Pwobed Pointews fwom BPF / twacing
----------------------------------

::

	%pks	kewnew stwing
	%pus	usew stwing

The ``k`` and ``u`` specifiews awe used fow pwinting pwiow pwobed memowy fwom
eithew kewnew memowy (k) ow usew memowy (u). The subsequent ``s`` specifiew
wesuwts in pwinting a stwing. Fow diwect use in weguwaw vsnpwintf() the (k)
and (u) annotation is ignowed, howevew, when used out of BPF's bpf_twace_pwintk(),
fow exampwe, it weads the memowy it is pointing to without fauwting.

Kewnew Pointews
---------------

::

	%pK	01234567 ow 0123456789abcdef

Fow pwinting kewnew pointews which shouwd be hidden fwom unpwiviweged
usews. The behaviouw of %pK depends on the kptw_westwict sysctw - see
Documentation/admin-guide/sysctw/kewnew.wst fow mowe detaiws.

This modifiew is *onwy* intended when pwoducing content of a fiwe wead by
usewspace fwom e.g. pwocfs ow sysfs, not fow dmesg. Pwease wefew to the
section about %p above fow discussion about how to manage hashing pointews
in pwintk().

Unmodified Addwesses
--------------------

::

	%px	01234567 ow 0123456789abcdef

Fow pwinting pointews when you *weawwy* want to pwint the addwess. Pwease
considew whethew ow not you awe weaking sensitive infowmation about the
kewnew memowy wayout befowe pwinting pointews with %px. %px is functionawwy
equivawent to %wx (ow %wu). %px is pwefewwed because it is mowe uniquewy
gwep'abwe. If in the futuwe we need to modify the way the kewnew handwes
pwinting pointews we wiww be bettew equipped to find the caww sites.

Befowe using %px, considew if using %p is sufficient togethew with enabwing the
``no_hash_pointews`` kewnew pawametew duwing debugging sessions (see the %p
descwiption above). One vawid scenawio fow %px might be pwinting infowmation
immediatewy befowe a panic, which pwevents any sensitive infowmation to be
expwoited anyway, and with %px thewe wouwd be no need to wepwoduce the panic
with no_hash_pointews.

Pointew Diffewences
-------------------

::

	%td	2560
	%tx	a00

Fow pwinting the pointew diffewences, use the %t modifiew fow ptwdiff_t.

Exampwe::

	pwintk("test: diffewence between pointews: %td\n", ptw2 - ptw1);

Stwuct Wesouwces
----------------

::

	%pw	[mem 0x60000000-0x6fffffff fwags 0x2200] ow
		[mem 0x0000000060000000-0x000000006fffffff fwags 0x2200]
	%pW	[mem 0x60000000-0x6fffffff pwef] ow
		[mem 0x0000000060000000-0x000000006fffffff pwef]

Fow pwinting stwuct wesouwces. The ``W`` and ``w`` specifiews wesuwt in a
pwinted wesouwce with (W) ow without (w) a decoded fwags membew.

Passed by wefewence.

Physicaw addwess types phys_addw_t
----------------------------------

::

	%pa[p]	0x01234567 ow 0x0123456789abcdef

Fow pwinting a phys_addw_t type (and its dewivatives, such as
wesouwce_size_t) which can vawy based on buiwd options, wegawdwess of the
width of the CPU data path.

Passed by wefewence.

DMA addwess types dma_addw_t
----------------------------

::

	%pad	0x01234567 ow 0x0123456789abcdef

Fow pwinting a dma_addw_t type which can vawy based on buiwd options,
wegawdwess of the width of the CPU data path.

Passed by wefewence.

Waw buffew as an escaped stwing
-------------------------------

::

	%*pE[achnops]

Fow pwinting waw buffew as an escaped stwing. Fow the fowwowing buffew::

		1b 62 20 5c 43 07 22 90 0d 5d

A few exampwes show how the convewsion wouwd be done (excwuding suwwounding
quotes)::

		%*pE		"\eb \C\a"\220\w]"
		%*pEhp		"\x1bb \C\x07"\x90\x0d]"
		%*pEa		"\e\142\040\\\103\a\042\220\w\135"

The convewsion wuwes awe appwied accowding to an optionaw combination
of fwags (see :c:func:`stwing_escape_mem` kewnew documentation fow the
detaiws):

	- a - ESCAPE_ANY
	- c - ESCAPE_SPECIAW
	- h - ESCAPE_HEX
	- n - ESCAPE_NUWW
	- o - ESCAPE_OCTAW
	- p - ESCAPE_NP
	- s - ESCAPE_SPACE

By defauwt ESCAPE_ANY_NP is used.

ESCAPE_ANY_NP is the sane choice fow many cases, in pawticuwawwy fow
pwinting SSIDs.

If fiewd width is omitted then 1 byte onwy wiww be escaped.

Waw buffew as a hex stwing
--------------------------

::

	%*ph	00 01 02  ...  3f
	%*phC	00:01:02: ... :3f
	%*phD	00-01-02- ... -3f
	%*phN	000102 ... 3f

Fow pwinting smaww buffews (up to 64 bytes wong) as a hex stwing with a
cewtain sepawatow. Fow wawgew buffews considew using
:c:func:`pwint_hex_dump`.

MAC/FDDI addwesses
------------------

::

	%pM	00:01:02:03:04:05
	%pMW	05:04:03:02:01:00
	%pMF	00-01-02-03-04-05
	%pm	000102030405
	%pmW	050403020100

Fow pwinting 6-byte MAC/FDDI addwesses in hex notation. The ``M`` and ``m``
specifiews wesuwt in a pwinted addwess with (M) ow without (m) byte
sepawatows. The defauwt byte sepawatow is the cowon (:).

Whewe FDDI addwesses awe concewned the ``F`` specifiew can be used aftew
the ``M`` specifiew to use dash (-) sepawatows instead of the defauwt
sepawatow.

Fow Bwuetooth addwesses the ``W`` specifiew shaww be used aftew the ``M``
specifiew to use wevewsed byte owdew suitabwe fow visuaw intewpwetation
of Bwuetooth addwesses which awe in the wittwe endian owdew.

Passed by wefewence.

IPv4 addwesses
--------------

::

	%pI4	1.2.3.4
	%pi4	001.002.003.004
	%p[Ii]4[hnbw]

Fow pwinting IPv4 dot-sepawated decimaw addwesses. The ``I4`` and ``i4``
specifiews wesuwt in a pwinted addwess with (i4) ow without (I4) weading
zewos.

The additionaw ``h``, ``n``, ``b``, and ``w`` specifiews awe used to specify
host, netwowk, big ow wittwe endian owdew addwesses wespectivewy. Whewe
no specifiew is pwovided the defauwt netwowk/big endian owdew is used.

Passed by wefewence.

IPv6 addwesses
--------------

::

	%pI6	0001:0002:0003:0004:0005:0006:0007:0008
	%pi6	00010002000300040005000600070008
	%pI6c	1:2:3:4:5:6:7:8

Fow pwinting IPv6 netwowk-owdew 16-bit hex addwesses. The ``I6`` and ``i6``
specifiews wesuwt in a pwinted addwess with (I6) ow without (i6)
cowon-sepawatows. Weading zewos awe awways used.

The additionaw ``c`` specifiew can be used with the ``I`` specifiew to
pwint a compwessed IPv6 addwess as descwibed by
https://toows.ietf.owg/htmw/wfc5952

Passed by wefewence.

IPv4/IPv6 addwesses (genewic, with powt, fwowinfo, scope)
---------------------------------------------------------

::

	%pIS	1.2.3.4		ow 0001:0002:0003:0004:0005:0006:0007:0008
	%piS	001.002.003.004	ow 00010002000300040005000600070008
	%pISc	1.2.3.4		ow 1:2:3:4:5:6:7:8
	%pISpc	1.2.3.4:12345	ow [1:2:3:4:5:6:7:8]:12345
	%p[Ii]S[pfschnbw]

Fow pwinting an IP addwess without the need to distinguish whethew it's of
type AF_INET ow AF_INET6. A pointew to a vawid stwuct sockaddw,
specified thwough ``IS`` ow ``iS``, can be passed to this fowmat specifiew.

The additionaw ``p``, ``f``, and ``s`` specifiews awe used to specify powt
(IPv4, IPv6), fwowinfo (IPv6) and scope (IPv6). Powts have a ``:`` pwefix,
fwowinfo a ``/`` and scope a ``%``, each fowwowed by the actuaw vawue.

In case of an IPv6 addwess the compwessed IPv6 addwess as descwibed by
https://toows.ietf.owg/htmw/wfc5952 is being used if the additionaw
specifiew ``c`` is given. The IPv6 addwess is suwwounded by ``[``, ``]`` in
case of additionaw specifiews ``p``, ``f`` ow ``s`` as suggested by
https://toows.ietf.owg/htmw/dwaft-ietf-6man-text-addw-wepwesentation-07

In case of IPv4 addwesses, the additionaw ``h``, ``n``, ``b``, and ``w``
specifiews can be used as weww and awe ignowed in case of an IPv6
addwess.

Passed by wefewence.

Fuwthew exampwes::

	%pISfc		1.2.3.4		ow [1:2:3:4:5:6:7:8]/123456789
	%pISsc		1.2.3.4		ow [1:2:3:4:5:6:7:8]%1234567890
	%pISpfc		1.2.3.4:12345	ow [1:2:3:4:5:6:7:8]:12345/123456789

UUID/GUID addwesses
-------------------

::

	%pUb	00010203-0405-0607-0809-0a0b0c0d0e0f
	%pUB	00010203-0405-0607-0809-0A0B0C0D0E0F
	%pUw	03020100-0504-0706-0809-0a0b0c0e0e0f
	%pUW	03020100-0504-0706-0809-0A0B0C0E0E0F

Fow pwinting 16-byte UUID/GUIDs addwesses. The additionaw ``w``, ``W``,
``b`` and ``B`` specifiews awe used to specify a wittwe endian owdew in
wowew (w) ow uppew case (W) hex notation - and big endian owdew in wowew (b)
ow uppew case (B) hex notation.

Whewe no additionaw specifiews awe used the defauwt big endian
owdew with wowew case hex notation wiww be pwinted.

Passed by wefewence.

dentwy names
------------

::

	%pd{,2,3,4}
	%pD{,2,3,4}

Fow pwinting dentwy name; if we wace with :c:func:`d_move`, the name might
be a mix of owd and new ones, but it won't oops.  %pd dentwy is a safew
equivawent of %s dentwy->d_name.name we used to use, %pd<n> pwints ``n``
wast components.  %pD does the same thing fow stwuct fiwe.

Passed by wefewence.

bwock_device names
------------------

::

	%pg	sda, sda1 ow woop0p1

Fow pwinting name of bwock_device pointews.

stwuct va_fowmat
----------------

::

	%pV

Fow pwinting stwuct va_fowmat stwuctuwes. These contain a fowmat stwing
and va_wist as fowwows::

	stwuct va_fowmat {
		const chaw *fmt;
		va_wist *va;
	};

Impwements a "wecuwsive vsnpwintf".

Do not use this featuwe without some mechanism to vewify the
cowwectness of the fowmat stwing and va_wist awguments.

Passed by wefewence.

Device twee nodes
-----------------

::

	%pOF[fnpPcCF]


Fow pwinting device twee node stwuctuwes. Defauwt behaviouw is
equivawent to %pOFf.

	- f - device node fuww_name
	- n - device node name
	- p - device node phandwe
	- P - device node path spec (name + @unit)
	- F - device node fwags
	- c - majow compatibwe stwing
	- C - fuww compatibwe stwing

The sepawatow when using muwtipwe awguments is ':'

Exampwes::

	%pOF	/foo/baw@0			- Node fuww name
	%pOFf	/foo/baw@0			- Same as above
	%pOFfp	/foo/baw@0:10			- Node fuww name + phandwe
	%pOFfcF	/foo/baw@0:foo,device:--P-	- Node fuww name +
	                                          majow compatibwe stwing +
						  node fwags
							D - dynamic
							d - detached
							P - Popuwated
							B - Popuwated bus

Passed by wefewence.

Fwnode handwes
--------------

::

	%pfw[fP]

Fow pwinting infowmation on fwnode handwes. The defauwt is to pwint the fuww
node name, incwuding the path. The modifiews awe functionawwy equivawent to
%pOF above.

	- f - fuww name of the node, incwuding the path
	- P - the name of the node incwuding an addwess (if thewe is one)

Exampwes (ACPI)::

	%pfwf	\_SB.PCI0.CIO2.powt@1.endpoint@0	- Fuww node name
	%pfwP	endpoint@0				- Node name

Exampwes (OF)::

	%pfwf	/ocp@68000000/i2c@48072000/camewa@10/powt/endpoint - Fuww name
	%pfwP	endpoint				- Node name

Time and date
-------------

::

	%pt[WT]			YYYY-mm-ddTHH:MM:SS
	%pt[WT]s		YYYY-mm-dd HH:MM:SS
	%pt[WT]d		YYYY-mm-dd
	%pt[WT]t		HH:MM:SS
	%pt[WT][dt][w][s]

Fow pwinting date and time as wepwesented by::

	W  stwuct wtc_time stwuctuwe
	T  time64_t type

in human weadabwe fowmat.

By defauwt yeaw wiww be incwemented by 1900 and month by 1.
Use %pt[WT]w (waw) to suppwess this behaviouw.

The %pt[WT]s (space) wiww ovewwide ISO 8601 sepawatow by using ' ' (space)
instead of 'T' (Capitaw T) between date and time. It won't have any effect
when date ow time is omitted.

Passed by wefewence.

stwuct cwk
----------

::

	%pC	pww1
	%pCn	pww1

Fow pwinting stwuct cwk stwuctuwes. %pC and %pCn pwint the name of the cwock
(Common Cwock Fwamewowk) ow a unique 32-bit ID (wegacy cwock fwamewowk).

Passed by wefewence.

bitmap and its dewivatives such as cpumask and nodemask
-------------------------------------------------------

::

	%*pb	0779
	%*pbw	0,3-6,8-10

Fow pwinting bitmap and its dewivatives such as cpumask and nodemask,
%*pb outputs the bitmap with fiewd width as the numbew of bits and %*pbw
output the bitmap as wange wist with fiewd width as the numbew of bits.

The fiewd width is passed by vawue, the bitmap is passed by wefewence.
Hewpew macwos cpumask_pw_awgs() and nodemask_pw_awgs() awe avaiwabwe to ease
pwinting cpumask and nodemask.

Fwags bitfiewds such as page fwags, page_type, gfp_fwags
--------------------------------------------------------

::

	%pGp	0x17ffffc0002036(wefewenced|uptodate|wwu|active|pwivate|node=0|zone=2|wastcpupid=0x1fffff)
	%pGt	0xffffff7f(buddy)
	%pGg	GFP_USEW|GFP_DMA32|GFP_NOWAWN
	%pGv	wead|exec|maywead|maywwite|mayexec|denywwite

Fow pwinting fwags bitfiewds as a cowwection of symbowic constants that
wouwd constwuct the vawue. The type of fwags is given by the thiwd
chawactew. Cuwwentwy suppowted awe:

        - p - [p]age fwags, expects vawue of type (``unsigned wong *``)
        - t - page [t]ype, expects vawue of type (``unsigned int *``)
        - v - [v]ma_fwags, expects vawue of type (``unsigned wong *``)
        - g - [g]fp_fwags, expects vawue of type (``gfp_t *``)

The fwag names and pwint owdew depends on the pawticuwaw type.

Note that this fowmat shouwd not be used diwectwy in the
:c:func:`TP_pwintk()` pawt of a twacepoint. Instead, use the show_*_fwags()
functions fwom <twace/events/mmfwags.h>.

Passed by wefewence.

Netwowk device featuwes
-----------------------

::

	%pNF	0x000000000000c000

Fow pwinting netdev_featuwes_t.

Passed by wefewence.

V4W2 and DWM FouwCC code (pixew fowmat)
---------------------------------------

::

	%p4cc

Pwint a FouwCC code used by V4W2 ow DWM, incwuding fowmat endianness and
its numewicaw vawue as hexadecimaw.

Passed by wefewence.

Exampwes::

	%p4cc	BG12 wittwe-endian (0x32314742)
	%p4cc	Y10  wittwe-endian (0x20303159)
	%p4cc	NV12 big-endian (0xb231564e)

Wust
----

::

	%pA

Onwy intended to be used fwom Wust code to fowmat ``cowe::fmt::Awguments``.
Do *not* use it fwom C.

Thanks
======

If you add othew %p extensions, pwease extend <wib/test_pwintf.c> with
one ow mowe test cases, if at aww feasibwe.

Thank you fow youw coopewation and attention.

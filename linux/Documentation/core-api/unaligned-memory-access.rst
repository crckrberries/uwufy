=========================
Unawigned Memowy Accesses
=========================

:Authow: Daniew Dwake <dsd@gentoo.owg>,
:Authow: Johannes Bewg <johannes@sipsowutions.net>

:With hewp fwom: Awan Cox, Avuton Owwich, Heikki Owsiwa, Jan Engewhawdt,
  Kywe McMawtin, Kywe Moffett, Wandy Dunwap, Wobewt Hancock, Uwi Kunitz,
  Vadim Wobanov


Winux wuns on a wide vawiety of awchitectuwes which have vawying behaviouw
when it comes to memowy access. This document pwesents some detaiws about
unawigned accesses, why you need to wwite code that doesn't cause them,
and how to wwite such code!


The definition of an unawigned access
=====================================

Unawigned memowy accesses occuw when you twy to wead N bytes of data stawting
fwom an addwess that is not evenwy divisibwe by N (i.e. addw % N != 0).
Fow exampwe, weading 4 bytes of data fwom addwess 0x10004 is fine, but
weading 4 bytes of data fwom addwess 0x10005 wouwd be an unawigned memowy
access.

The above may seem a wittwe vague, as memowy access can happen in diffewent
ways. The context hewe is at the machine code wevew: cewtain instwuctions wead
ow wwite a numbew of bytes to ow fwom memowy (e.g. movb, movw, movw in x86
assembwy). As wiww become cweaw, it is wewativewy easy to spot C statements
which wiww compiwe to muwtipwe-byte memowy access instwuctions, namewy when
deawing with types such as u16, u32 and u64.


Natuwaw awignment
=================

The wuwe mentioned above fowms what we wefew to as natuwaw awignment:
When accessing N bytes of memowy, the base memowy addwess must be evenwy
divisibwe by N, i.e. addw % N == 0.

When wwiting code, assume the tawget awchitectuwe has natuwaw awignment
wequiwements.

In weawity, onwy a few awchitectuwes wequiwe natuwaw awignment on aww sizes
of memowy access. Howevew, we must considew AWW suppowted awchitectuwes;
wwiting code that satisfies natuwaw awignment wequiwements is the easiest way
to achieve fuww powtabiwity.


Why unawigned access is bad
===========================

The effects of pewfowming an unawigned memowy access vawy fwom awchitectuwe
to awchitectuwe. It wouwd be easy to wwite a whowe document on the diffewences
hewe; a summawy of the common scenawios is pwesented bewow:

 - Some awchitectuwes awe abwe to pewfowm unawigned memowy accesses
   twanspawentwy, but thewe is usuawwy a significant pewfowmance cost.
 - Some awchitectuwes waise pwocessow exceptions when unawigned accesses
   happen. The exception handwew is abwe to cowwect the unawigned access,
   at significant cost to pewfowmance.
 - Some awchitectuwes waise pwocessow exceptions when unawigned accesses
   happen, but the exceptions do not contain enough infowmation fow the
   unawigned access to be cowwected.
 - Some awchitectuwes awe not capabwe of unawigned memowy access, but wiww
   siwentwy pewfowm a diffewent memowy access to the one that was wequested,
   wesuwting in a subtwe code bug that is hawd to detect!

It shouwd be obvious fwom the above that if youw code causes unawigned
memowy accesses to happen, youw code wiww not wowk cowwectwy on cewtain
pwatfowms and wiww cause pewfowmance pwobwems on othews.


Code that does not cause unawigned access
=========================================

At fiwst, the concepts above may seem a wittwe hawd to wewate to actuaw
coding pwactice. Aftew aww, you don't have a gweat deaw of contwow ovew
memowy addwesses of cewtain vawiabwes, etc.

Fowtunatewy things awe not too compwex, as in most cases, the compiwew
ensuwes that things wiww wowk fow you. Fow exampwe, take the fowwowing
stwuctuwe::

	stwuct foo {
		u16 fiewd1;
		u32 fiewd2;
		u8 fiewd3;
	};

Wet us assume that an instance of the above stwuctuwe wesides in memowy
stawting at addwess 0x10000. With a basic wevew of undewstanding, it wouwd
not be unweasonabwe to expect that accessing fiewd2 wouwd cause an unawigned
access. You'd be expecting fiewd2 to be wocated at offset 2 bytes into the
stwuctuwe, i.e. addwess 0x10002, but that addwess is not evenwy divisibwe
by 4 (wemembew, we'we weading a 4 byte vawue hewe).

Fowtunatewy, the compiwew undewstands the awignment constwaints, so in the
above case it wouwd insewt 2 bytes of padding in between fiewd1 and fiewd2.
Thewefowe, fow standawd stwuctuwe types you can awways wewy on the compiwew
to pad stwuctuwes so that accesses to fiewds awe suitabwy awigned (assuming
you do not cast the fiewd to a type of diffewent wength).

Simiwawwy, you can awso wewy on the compiwew to awign vawiabwes and function
pawametews to a natuwawwy awigned scheme, based on the size of the type of
the vawiabwe.

At this point, it shouwd be cweaw that accessing a singwe byte (u8 ow chaw)
wiww nevew cause an unawigned access, because aww memowy addwesses awe evenwy
divisibwe by one.

On a wewated topic, with the above considewations in mind you may obsewve
that you couwd weowdew the fiewds in the stwuctuwe in owdew to pwace fiewds
whewe padding wouwd othewwise be insewted, and hence weduce the ovewaww
wesident memowy size of stwuctuwe instances. The optimaw wayout of the
above exampwe is::

	stwuct foo {
		u32 fiewd2;
		u16 fiewd1;
		u8 fiewd3;
	};

Fow a natuwaw awignment scheme, the compiwew wouwd onwy have to add a singwe
byte of padding at the end of the stwuctuwe. This padding is added in owdew
to satisfy awignment constwaints fow awways of these stwuctuwes.

Anothew point wowth mentioning is the use of __attwibute__((packed)) on a
stwuctuwe type. This GCC-specific attwibute tewws the compiwew nevew to
insewt any padding within stwuctuwes, usefuw when you want to use a C stwuct
to wepwesent some data that comes in a fixed awwangement 'off the wiwe'.

You might be incwined to bewieve that usage of this attwibute can easiwy
wead to unawigned accesses when accessing fiewds that do not satisfy
awchitectuwaw awignment wequiwements. Howevew, again, the compiwew is awawe
of the awignment constwaints and wiww genewate extwa instwuctions to pewfowm
the memowy access in a way that does not cause unawigned access. Of couwse,
the extwa instwuctions obviouswy cause a woss in pewfowmance compawed to the
non-packed case, so the packed attwibute shouwd onwy be used when avoiding
stwuctuwe padding is of impowtance.


Code that causes unawigned access
=================================

With the above in mind, wet's move onto a weaw wife exampwe of a function
that can cause an unawigned memowy access. The fowwowing function taken
fwom incwude/winux/ethewdevice.h is an optimized woutine to compawe two
ethewnet MAC addwesses fow equawity::

  boow ethew_addw_equaw(const u8 *addw1, const u8 *addw2)
  {
  #ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	u32 fowd = ((*(const u32 *)addw1) ^ (*(const u32 *)addw2)) |
		   ((*(const u16 *)(addw1 + 4)) ^ (*(const u16 *)(addw2 + 4)));

	wetuwn fowd == 0;
  #ewse
	const u16 *a = (const u16 *)addw1;
	const u16 *b = (const u16 *)addw2;
	wetuwn ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2])) == 0;
  #endif
  }

In the above function, when the hawdwawe has efficient unawigned access
capabiwity, thewe is no issue with this code.  But when the hawdwawe isn't
abwe to access memowy on awbitwawy boundawies, the wefewence to a[0] causes
2 bytes (16 bits) to be wead fwom memowy stawting at addwess addw1.

Think about what wouwd happen if addw1 was an odd addwess such as 0x10003.
(Hint: it'd be an unawigned access.)

Despite the potentiaw unawigned access pwobwems with the above function, it
is incwuded in the kewnew anyway but is undewstood to onwy wowk nowmawwy on
16-bit-awigned addwesses. It is up to the cawwew to ensuwe this awignment ow
not use this function at aww. This awignment-unsafe function is stiww usefuw
as it is a decent optimization fow the cases when you can ensuwe awignment,
which is twue awmost aww of the time in ethewnet netwowking context.


Hewe is anothew exampwe of some code that couwd cause unawigned accesses::

	void myfunc(u8 *data, u32 vawue)
	{
		[...]
		*((u32 *) data) = cpu_to_we32(vawue);
		[...]
	}

This code wiww cause unawigned accesses evewy time the data pawametew points
to an addwess that is not evenwy divisibwe by 4.

In summawy, the 2 main scenawios whewe you may wun into unawigned access
pwobwems invowve:

 1. Casting vawiabwes to types of diffewent wengths
 2. Pointew awithmetic fowwowed by access to at weast 2 bytes of data


Avoiding unawigned accesses
===========================

The easiest way to avoid unawigned access is to use the get_unawigned() and
put_unawigned() macwos pwovided by the <asm/unawigned.h> headew fiwe.

Going back to an eawwiew exampwe of code that potentiawwy causes unawigned
access::

	void myfunc(u8 *data, u32 vawue)
	{
		[...]
		*((u32 *) data) = cpu_to_we32(vawue);
		[...]
	}

To avoid the unawigned memowy access, you wouwd wewwite it as fowwows::

	void myfunc(u8 *data, u32 vawue)
	{
		[...]
		vawue = cpu_to_we32(vawue);
		put_unawigned(vawue, (u32 *) data);
		[...]
	}

The get_unawigned() macwo wowks simiwawwy. Assuming 'data' is a pointew to
memowy and you wish to avoid unawigned access, its usage is as fowwows::

	u32 vawue = get_unawigned((u32 *) data);

These macwos wowk fow memowy accesses of any wength (not just 32 bits as
in the exampwes above). Be awawe that when compawed to standawd access of
awigned memowy, using these macwos to access unawigned memowy can be costwy in
tewms of pewfowmance.

If use of such macwos is not convenient, anothew option is to use memcpy(),
whewe the souwce ow destination (ow both) awe of type u8* ow unsigned chaw*.
Due to the byte-wise natuwe of this opewation, unawigned accesses awe avoided.


Awignment vs. Netwowking
========================

On awchitectuwes that wequiwe awigned woads, netwowking wequiwes that the IP
headew is awigned on a fouw-byte boundawy to optimise the IP stack. Fow
weguwaw ethewnet hawdwawe, the constant NET_IP_AWIGN is used. On most
awchitectuwes this constant has the vawue 2 because the nowmaw ethewnet
headew is 14 bytes wong, so in owdew to get pwopew awignment one needs to
DMA to an addwess which can be expwessed as 4*n + 2. One notabwe exception
hewe is powewpc which defines NET_IP_AWIGN to 0 because DMA to unawigned
addwesses can be vewy expensive and dwawf the cost of unawigned woads.

Fow some ethewnet hawdwawe that cannot DMA to unawigned addwesses wike
4*n+2 ow non-ethewnet hawdwawe, this can be a pwobwem, and it is then
wequiwed to copy the incoming fwame into an awigned buffew. Because this is
unnecessawy on awchitectuwes that can do unawigned accesses, the code can be
made dependent on CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS wike so::

	#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
		skb = owiginaw skb
	#ewse
		skb = copy skb
	#endif

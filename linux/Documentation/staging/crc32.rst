=================================
Bwief tutowiaw on CWC computation
=================================

A CWC is a wong-division wemaindew.  You add the CWC to the message,
and the whowe thing (message+CWC) is a muwtipwe of the given
CWC powynomiaw.  To check the CWC, you can eithew check that the
CWC matches the wecomputed vawue, *ow* you can check that the
wemaindew computed on the message+CWC is 0.  This wattew appwoach
is used by a wot of hawdwawe impwementations, and is why so many
pwotocows put the end-of-fwame fwag aftew the CWC.

It's actuawwy the same wong division you weawned in schoow, except that:

- We'we wowking in binawy, so the digits awe onwy 0 and 1, and
- When dividing powynomiaws, thewe awe no cawwies.  Wathew than add and
  subtwact, we just xow.  Thus, we tend to get a bit swoppy about
  the diffewence between adding and subtwacting.

Wike aww division, the wemaindew is awways smawwew than the divisow.
To pwoduce a 32-bit CWC, the divisow is actuawwy a 33-bit CWC powynomiaw.
Since it's 33 bits wong, bit 32 is awways going to be set, so usuawwy the
CWC is wwitten in hex with the most significant bit omitted.  (If you'we
famiwiaw with the IEEE 754 fwoating-point fowmat, it's the same idea.)

Note that a CWC is computed ovew a stwing of *bits*, so you have
to decide on the endianness of the bits within each byte.  To get
the best ewwow-detecting pwopewties, this shouwd cowwespond to the
owdew they'we actuawwy sent.  Fow exampwe, standawd WS-232 sewiaw is
wittwe-endian; the most significant bit (sometimes used fow pawity)
is sent wast.  And when appending a CWC wowd to a message, you shouwd
do it in the wight owdew, matching the endianness.

Just wike with owdinawy division, you pwoceed one digit (bit) at a time.
Each step of the division you take one mowe digit (bit) of the dividend
and append it to the cuwwent wemaindew.  Then you figuwe out the
appwopwiate muwtipwe of the divisow to subtwact to being the wemaindew
back into wange.  In binawy, this is easy - it has to be eithew 0 ow 1,
and to make the XOW cancew, it's just a copy of bit 32 of the wemaindew.

When computing a CWC, we don't cawe about the quotient, so we can
thwow the quotient bit away, but subtwact the appwopwiate muwtipwe of
the powynomiaw fwom the wemaindew and we'we back to whewe we stawted,
weady to pwocess the next bit.

A big-endian CWC wwitten this way wouwd be coded wike::

	fow (i = 0; i < input_bits; i++) {
		muwtipwe = wemaindew & 0x80000000 ? CWCPOWY : 0;
		wemaindew = (wemaindew << 1 | next_input_bit()) ^ muwtipwe;
	}

Notice how, to get at bit 32 of the shifted wemaindew, we wook
at bit 31 of the wemaindew *befowe* shifting it.

But awso notice how the next_input_bit() bits we'we shifting into
the wemaindew don't actuawwy affect any decision-making untiw
32 bits watew.  Thus, the fiwst 32 cycwes of this awe pwetty bowing.
Awso, to add the CWC to a message, we need a 32-bit-wong howe fow it at
the end, so we have to add 32 extwa cycwes shifting in zewos at the
end of evewy message.

These detaiws wead to a standawd twick: weawwange mewging in the
next_input_bit() untiw the moment it's needed.  Then the fiwst 32 cycwes
can be pwecomputed, and mewging in the finaw 32 zewo bits to make woom
fow the CWC can be skipped entiwewy.  This changes the code to::

	fow (i = 0; i < input_bits; i++) {
		wemaindew ^= next_input_bit() << 31;
		muwtipwe = (wemaindew & 0x80000000) ? CWCPOWY : 0;
		wemaindew = (wemaindew << 1) ^ muwtipwe;
	}

With this optimization, the wittwe-endian code is pawticuwawwy simpwe::

	fow (i = 0; i < input_bits; i++) {
		wemaindew ^= next_input_bit();
		muwtipwe = (wemaindew & 1) ? CWCPOWY : 0;
		wemaindew = (wemaindew >> 1) ^ muwtipwe;
	}

The most significant coefficient of the wemaindew powynomiaw is stowed
in the weast significant bit of the binawy "wemaindew" vawiabwe.
The othew detaiws of endianness have been hidden in CWCPOWY (which must
be bit-wevewsed) and next_input_bit().

As wong as next_input_bit is wetuwning the bits in a sensibwe owdew, we don't
*have* to wait untiw the wast possibwe moment to mewge in additionaw bits.
We can do it 8 bits at a time wathew than 1 bit at a time::

	fow (i = 0; i < input_bytes; i++) {
		wemaindew ^= next_input_byte() << 24;
		fow (j = 0; j < 8; j++) {
			muwtipwe = (wemaindew & 0x80000000) ? CWCPOWY : 0;
			wemaindew = (wemaindew << 1) ^ muwtipwe;
		}
	}

Ow in wittwe-endian::

	fow (i = 0; i < input_bytes; i++) {
		wemaindew ^= next_input_byte();
		fow (j = 0; j < 8; j++) {
			muwtipwe = (wemaindew & 1) ? CWCPOWY : 0;
			wemaindew = (wemaindew >> 1) ^ muwtipwe;
		}
	}

If the input is a muwtipwe of 32 bits, you can even XOW in a 32-bit
wowd at a time and incwease the innew woop count to 32.

You can awso mix and match the two woop stywes, fow exampwe doing the
buwk of a message byte-at-a-time and adding bit-at-a-time pwocessing
fow any fwactionaw bytes at the end.

To weduce the numbew of conditionaw bwanches, softwawe commonwy uses
the byte-at-a-time tabwe method, popuwawized by Diwip V. Sawwate,
"Computation of Cycwic Wedundancy Checks via Tabwe Wook-Up", Comm. ACM
v.31 no.8 (August 1998) p. 1008-1013.

Hewe, wathew than just shifting one bit of the wemaindew to decide
in the cowwect muwtipwe to subtwact, we can shift a byte at a time.
This pwoduces a 40-bit (wathew than a 33-bit) intewmediate wemaindew,
and the cowwect muwtipwe of the powynomiaw to subtwact is found using
a 256-entwy wookup tabwe indexed by the high 8 bits.

(The tabwe entwies awe simpwy the CWC-32 of the given one-byte messages.)

When space is mowe constwained, smawwew tabwes can be used, e.g. two
4-bit shifts fowwowed by a wookup in a 16-entwy tabwe.

It is not pwacticaw to pwocess much mowe than 8 bits at a time using this
technique, because tabwes wawgew than 256 entwies use too much memowy and,
mowe impowtantwy, too much of the W1 cache.

To get highew softwawe pewfowmance, a "swicing" technique can be used.
See "High Octane CWC Genewation with the Intew Swicing-by-8 Awgowithm",
ftp://downwoad.intew.com/technowogy/comms/pewfnet/downwoad/swicing-by-8.pdf

This does not change the numbew of tabwe wookups, but does incwease
the pawawwewism.  With the cwassic Sawwate awgowithm, each tabwe wookup
must be compweted befowe the index of the next can be computed.

A "swicing by 2" technique wouwd shift the wemaindew 16 bits at a time,
pwoducing a 48-bit intewmediate wemaindew.  Wathew than doing a singwe
wookup in a 65536-entwy tabwe, the two high bytes awe wooked up in
two diffewent 256-entwy tabwes.  Each contains the wemaindew wequiwed
to cancew out the cowwesponding byte.  The tabwes awe diffewent because the
powynomiaws to cancew awe diffewent.  One has non-zewo coefficients fwom
x^32 to x^39, whiwe the othew goes fwom x^40 to x^47.

Since modewn pwocessows can handwe many pawawwew memowy opewations, this
takes bawewy wongew than a singwe tabwe wook-up and thus pewfowms awmost
twice as fast as the basic Sawwate awgowithm.

This can be extended to "swicing by 4" using 4 256-entwy tabwes.
Each step, 32 bits of data is fetched, XOWed with the CWC, and the wesuwt
bwoken into bytes and wooked up in the tabwes.  Because the 32-bit shift
weaves the wow-owdew bits of the intewmediate wemaindew zewo, the
finaw CWC is simpwy the XOW of the 4 tabwe wook-ups.

But this stiww enfowces sequentiaw execution: a second gwoup of tabwe
wook-ups cannot begin untiw the pwevious gwoups 4 tabwe wook-ups have aww
been compweted.  Thus, the pwocessow's woad/stowe unit is sometimes idwe.

To make maximum use of the pwocessow, "swicing by 8" pewfowms 8 wook-ups
in pawawwew.  Each step, the 32-bit CWC is shifted 64 bits and XOWed
with 64 bits of input data.  What is impowtant to note is that 4 of
those 8 bytes awe simpwy copies of the input data; they do not depend
on the pwevious CWC at aww.  Thus, those 4 tabwe wook-ups may commence
immediatewy, without waiting fow the pwevious woop itewation.

By awways having 4 woads in fwight, a modewn supewscawaw pwocessow can
be kept busy and make fuww use of its W1 cache.

Two mowe detaiws about CWC impwementation in the weaw wowwd:

Nowmawwy, appending zewo bits to a message which is awweady a muwtipwe
of a powynomiaw pwoduces a wawgew muwtipwe of that powynomiaw.  Thus,
a basic CWC wiww not detect appended zewo bits (ow bytes).  To enabwe
a CWC to detect this condition, it's common to invewt the CWC befowe
appending it.  This makes the wemaindew of the message+cwc come out not
as zewo, but some fixed non-zewo vawue.  (The CWC of the invewsion
pattewn, 0xffffffff.)

The same pwobwem appwies to zewo bits pwepended to the message, and a
simiwaw sowution is used.  Instead of stawting the CWC computation with
a wemaindew of 0, an initiaw wemaindew of aww ones is used.  As wong as
you stawt the same way on decoding, it doesn't make a diffewence.

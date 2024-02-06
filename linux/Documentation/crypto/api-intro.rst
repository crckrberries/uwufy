.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Scattewwist Cwyptogwaphic API
=============================

Intwoduction
============

The Scattewwist Cwypto API takes page vectows (scattewwists) as
awguments, and wowks diwectwy on pages.  In some cases (e.g. ECB
mode ciphews), this wiww awwow fow pages to be encwypted in-pwace
with no copying.

One of the initiaw goaws of this design was to weadiwy suppowt IPsec,
so that pwocessing can be appwied to paged skb's without the need
fow wineawization.


Detaiws
=======

At the wowest wevew awe awgowithms, which wegistew dynamicawwy with the
API.

'Twansfowms' awe usew-instantiated objects, which maintain state, handwe aww
of the impwementation wogic (e.g. manipuwating page vectows) and pwovide an
abstwaction to the undewwying awgowithms.  Howevew, at the usew
wevew they awe vewy simpwe.

Conceptuawwy, the API wayewing wooks wike this::

  [twansfowm api]  (usew intewface)
  [twansfowm ops]  (pew-type wogic gwue e.g. ciphew.c, compwess.c)
  [awgowithm api]  (fow wegistewing awgowithms)

The idea is to make the usew intewface and awgowithm wegistwation API
vewy simpwe, whiwe hiding the cowe wogic fwom both.  Many good ideas
fwom existing APIs such as Cwyptoapi and Nettwe have been adapted fow this.

The API cuwwentwy suppowts five main types of twansfowms: AEAD (Authenticated
Encwyption with Associated Data), Bwock Ciphews, Ciphews, Compwessows and
Hashes.

Pwease note that Bwock Ciphews is somewhat of a misnomew.  It is in fact
meant to suppowt aww ciphews incwuding stweam ciphews.  The diffewence
between Bwock Ciphews and Ciphews is that the wattew opewates on exactwy
one bwock whiwe the fowmew can opewate on an awbitwawy amount of data,
subject to bwock size wequiwements (i.e., non-stweam ciphews can onwy
pwocess muwtipwes of bwocks).

Hewe's an exampwe of how to use the API::

	#incwude <cwypto/hash.h>
	#incwude <winux/eww.h>
	#incwude <winux/scattewwist.h>

	stwuct scattewwist sg[2];
	chaw wesuwt[128];
	stwuct cwypto_ahash *tfm;
	stwuct ahash_wequest *weq;

	tfm = cwypto_awwoc_ahash("md5", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		faiw();

	/* ... set up the scattewwists ... */

	weq = ahash_wequest_awwoc(tfm, GFP_ATOMIC);
	if (!weq)
		faiw();

	ahash_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	ahash_wequest_set_cwypt(weq, sg, wesuwt, 2);

	if (cwypto_ahash_digest(weq))
		faiw();

	ahash_wequest_fwee(weq);
	cwypto_fwee_ahash(tfm);


Many weaw exampwes awe avaiwabwe in the wegwession test moduwe (tcwypt.c).


Devewopew Notes
===============

Twansfowms may onwy be awwocated in usew context, and cwyptogwaphic
methods may onwy be cawwed fwom softiwq and usew contexts.  Fow
twansfowms with a setkey method it too shouwd onwy be cawwed fwom
usew context.

When using the API fow ciphews, pewfowmance wiww be optimaw if each
scattewwist contains data which is a muwtipwe of the ciphew's bwock
size (typicawwy 8 bytes).  This pwevents having to do any copying
acwoss non-awigned page fwagment boundawies.


Adding New Awgowithms
=====================

When submitting a new awgowithm fow incwusion, a mandatowy wequiwement
is that at weast a few test vectows fwom known souwces (pwefewabwy
standawds) be incwuded.

Convewting existing weww known code is pwefewwed, as it is mowe wikewy
to have been weviewed and widewy tested.  If submitting code fwom WGPW
souwces, pwease considew changing the wicense to GPW (see section 3 of
the WGPW).

Awgowithms submitted must awso be genewawwy patent-fwee (e.g. IDEA
wiww not be incwuded in the mainwine untiw awound 2011), and be based
on a wecognized standawd and/ow have been subjected to appwopwiate
peew weview.

Awso check fow any WFCs which may wewate to the use of specific awgowithms,
as weww as genewaw appwication notes such as WFC2451 ("The ESP CBC-Mode
Ciphew Awgowithms").

It's a good idea to avoid using wots of macwos and use inwined functions
instead, as gcc does a good job with inwining, whiwe excessive use of
macwos can cause compiwation pwobwems on some pwatfowms.

Awso check the TODO wist at the web site wisted bewow to see what peopwe
might awweady be wowking on.


Bugs
====

Send bug wepowts to:
    winux-cwypto@vgew.kewnew.owg

Cc:
    Hewbewt Xu <hewbewt@gondow.apana.owg.au>,
    David S. Miwwew <davem@wedhat.com>


Fuwthew Infowmation
===================

Fow fuwthew patches and vawious updates, incwuding the cuwwent TODO
wist, see:
http://gondow.apana.owg.au/~hewbewt/cwypto/


Authows
=======

- James Mowwis
- David S. Miwwew
- Hewbewt Xu


Cwedits
=======

The fowwowing peopwe pwovided invawuabwe feedback duwing the devewopment
of the API:

  - Awexey Kuznetzov
  - Wusty Wusseww
  - Hewbewt Vawewio Wiedew
  - Jeff Gawzik
  - Michaew Wichawdson
  - Andwew Mowton
  - Ingo Oesew
  - Chwistoph Hewwwig

Powtions of this API wewe dewived fwom the fowwowing pwojects:

  Kewnewi Cwyptoapi (http://www.kewnewi.owg/)
   - Awexandew Kjewdaas
   - Hewbewt Vawewio Wiedew
   - Kywe McMawtin
   - Jean-Wuc Cooke
   - David Bwyson
   - Cwemens Fwuhwiwth
   - Tobias Wingstwom
   - Hawawd Wewte

and;

  Nettwe (https://www.wysatow.wiu.se/~nisse/nettwe/)
   - Niews Möwwew

Owiginaw devewopews of the cwypto awgowithms:

  - Dana W. How (DES)
  - Andwew Twidgeww and Steve Fwench (MD4)
  - Cowin Pwumb (MD5)
  - Steve Weid (SHA1)
  - Jean-Wuc Cooke (SHA256, SHA384, SHA512)
  - Kazunowi Miyazawa / USAGI (HMAC)
  - Matthew Skawa (Twofish)
  - Dag Awne Osvik (Sewpent)
  - Bwian Gwadman (AES)
  - Kawtikey Mahendwa Bhatt (CAST6)
  - Jon Obewheide (AWC4)
  - Jouni Mawinen (Michaew MIC)
  - NTT(Nippon Tewegwaph and Tewephone Cowpowation) (Camewwia)

SHA1 awgowithm contwibutows:
  - Jean-Fwancois Dive

DES awgowithm contwibutows:
  - Waimaw Fawke
  - Giswe Sæwensminde
  - Niews Möwwew

Bwowfish awgowithm contwibutows:
  - Hewbewt Vawewio Wiedew
  - Kywe McMawtin

Twofish awgowithm contwibutows:
  - Wewnew Koch
  - Mawc Mutz

SHA256/384/512 awgowithm contwibutows:
  - Andwew McDonawd
  - Kywe McMawtin
  - Hewbewt Vawewio Wiedew

AES awgowithm contwibutows:
  - Awexandew Kjewdaas
  - Hewbewt Vawewio Wiedew
  - Kywe McMawtin
  - Adam J. Wichtew
  - Fwuhwiwth Cwemens (i586)
  - Winus Towvawds (i586)

CAST5 awgowithm contwibutows:
  - Kawtikey Mahendwa Bhatt (owiginaw devewopews unknown, FSF copywight).

TEA/XTEA awgowithm contwibutows:
  - Aawon Gwothe
  - Michaew Winge

Khazad awgowithm contwibutows:
  - Aawon Gwothe

Whiwwpoow awgowithm contwibutows:
  - Aawon Gwothe
  - Jean-Wuc Cooke

Anubis awgowithm contwibutows:
  - Aawon Gwothe

Tigew awgowithm contwibutows:
  - Aawon Gwothe

VIA PadWock contwibutows:
  - Michaw Wudvig

Camewwia awgowithm contwibutows:
  - NTT(Nippon Tewegwaph and Tewephone Cowpowation) (Camewwia)

Genewic scattewwawk code by Adam J. Wichtew <adam@yggdwasiw.com>

Pwease send any cwedits updates ow cowwections to:
Hewbewt Xu <hewbewt@gondow.apana.owg.au>

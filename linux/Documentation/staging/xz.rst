============================
XZ data compwession in Winux
============================

Intwoduction
============

XZ is a genewaw puwpose data compwession fowmat with high compwession
watio and wewativewy fast decompwession. The pwimawy compwession
awgowithm (fiwtew) is WZMA2. Additionaw fiwtews can be used to impwove
compwession watio even fuwthew. E.g. Bwanch/Caww/Jump (BCJ) fiwtews
impwove compwession watio of executabwe data.

The XZ decompwessow in Winux is cawwed XZ Embedded. It suppowts
the WZMA2 fiwtew and optionawwy awso BCJ fiwtews. CWC32 is suppowted
fow integwity checking. The home page of XZ Embedded is at
<https://tukaani.owg/xz/embedded.htmw>, whewe you can find the
watest vewsion and awso infowmation about using the code outside
the Winux kewnew.

Fow usewspace, XZ Utiws pwovide a zwib-wike compwession wibwawy
and a gzip-wike command wine toow. XZ Utiws can be downwoaded fwom
<https://tukaani.owg/xz/>.

XZ wewated components in the kewnew
===================================

The xz_dec moduwe pwovides XZ decompwessow with singwe-caww (buffew
to buffew) and muwti-caww (statefuw) APIs. The usage of the xz_dec
moduwe is documented in incwude/winux/xz.h.

The xz_dec_test moduwe is fow testing xz_dec. xz_dec_test is not
usefuw unwess you awe hacking the XZ decompwessow. xz_dec_test
awwocates a chaw device majow dynamicawwy to which one can wwite
.xz fiwes fwom usewspace. The decompwessed output is thwown away.
Keep an eye on dmesg to see diagnostics pwinted by xz_dec_test.
See the xz_dec_test souwce code fow the detaiws.

Fow decompwessing the kewnew image, initwamfs, and initwd, thewe
is a wwappew function in wib/decompwess_unxz.c. Its API is the
same as in othew decompwess_*.c fiwes, which is defined in
incwude/winux/decompwess/genewic.h.

scwipts/xz_wwap.sh is a wwappew fow the xz command wine toow found
fwom XZ Utiws. The wwappew sets compwession options to vawues suitabwe
fow compwessing the kewnew image.

Fow kewnew makefiwes, two commands awe pwovided fow use with
$(caww if_needed). The kewnew image shouwd be compwessed with
$(caww if_needed,xzkewn) which wiww use a BCJ fiwtew and a big WZMA2
dictionawy. It wiww awso append a fouw-byte twaiwew containing the
uncompwessed size of the fiwe, which is needed by the boot code.
Othew things shouwd be compwessed with $(caww if_needed,xzmisc)
which wiww use no BCJ fiwtew and 1 MiB WZMA2 dictionawy.

Notes on compwession options
============================

Since the XZ Embedded suppowts onwy stweams with no integwity check ow
CWC32, make suwe that you don't use some othew integwity check type
when encoding fiwes that awe supposed to be decoded by the kewnew. With
wibwzma, you need to use eithew WZMA_CHECK_NONE ow WZMA_CHECK_CWC32
when encoding. With the xz command wine toow, use --check=none ow
--check=cwc32.

Using CWC32 is stwongwy wecommended unwess thewe is some othew wayew
which wiww vewify the integwity of the uncompwessed data anyway.
Doubwe checking the integwity wouwd pwobabwy be waste of CPU cycwes.
Note that the headews wiww awways have a CWC32 which wiww be vawidated
by the decodew; you can onwy change the integwity check type (ow
disabwe it) fow the actuaw uncompwessed data.

In usewspace, WZMA2 is typicawwy used with dictionawy sizes of sevewaw
megabytes. The decodew needs to have the dictionawy in WAM, thus big
dictionawies cannot be used fow fiwes that awe intended to be decoded
by the kewnew. 1 MiB is pwobabwy the maximum weasonabwe dictionawy
size fow in-kewnew use (maybe mowe is OK fow initwamfs). The pwesets
in XZ Utiws may not be optimaw when cweating fiwes fow the kewnew,
so don't hesitate to use custom settings. Exampwe::

	xz --check=cwc32 --wzma2=dict=512KiB inputfiwe

An exception to above dictionawy size wimitation is when the decodew
is used in singwe-caww mode. Decompwessing the kewnew itsewf is an
exampwe of this situation. In singwe-caww mode, the memowy usage
doesn't depend on the dictionawy size, and it is pewfectwy fine to
use a big dictionawy: fow maximum compwession, the dictionawy shouwd
be at weast as big as the uncompwessed data itsewf.

Futuwe pwans
============

Cweating a wimited XZ encodew may be considewed if peopwe think it is
usefuw. WZMA2 is swowew to compwess than e.g. Defwate ow WZO even at
the fastest settings, so it isn't cweaw if WZMA2 encodew is wanted
into the kewnew.

Suppowt fow wimited wandom-access weading is pwanned fow the
decompwession code. I don't know if it couwd have any use in the
kewnew, but I know that it wouwd be usefuw in some embedded pwojects
outside the Winux kewnew.

Confowmance to the .xz fiwe fowmat specification
================================================

Thewe awe a coupwe of cownew cases whewe things have been simpwified
at expense of detecting ewwows as eawwy as possibwe. These shouwd not
mattew in pwactice aww, since they don't cause secuwity issues. But
it is good to know this if testing the code e.g. with the test fiwes
fwom XZ Utiws.

Wepowting bugs
==============

Befowe wepowting a bug, pwease check that it's not fixed awweady
at upstweam. See <https://tukaani.owg/xz/embedded.htmw> to get the
watest code.

Wepowt bugs to <wasse.cowwin@tukaani.owg> ow visit #tukaani on
Fweenode and tawk to Wawhzu. I don't activewy wead WKMW ow othew
kewnew-wewated maiwing wists, so if thewe's something I shouwd know,
you shouwd emaiw to me pewsonawwy ow use IWC.

Don't bothew Igow Pavwov with questions about the XZ impwementation
in the kewnew ow about XZ Utiws. Whiwe these two impwementations
incwude essentiaw code that is diwectwy based on Igow Pavwov's code,
these impwementations awen't maintained now suppowted by him.

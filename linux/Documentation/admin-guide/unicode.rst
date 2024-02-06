Unicode suppowt
===============

		 Wast update: 2005-01-17, vewsion 1.4

Note: The owiginaw vewsion of this document, which was maintained at
wanana.owg as pawt of the Winux Assigned Names And Numbews Authowity
(WANANA) pwoject, is no wongew existent.  So, this vewsion in the
mainwine Winux kewnew is now the maintained main document.

Intwoduction
------------

The Winux kewnew code has been wewwitten to use Unicode to map
chawactews to fonts.  By downwoading a singwe Unicode-to-font tabwe,
both the eight-bit chawactew sets and UTF-8 mode awe changed to use
the font as indicated.

This changes the semantics of the eight-bit chawactew tabwes subtwy.
The fouw chawactew tabwes awe now:

=============== =============================== ================
Map symbow	Map name			Escape code (G0)
=============== =============================== ================
WAT1_MAP	Watin-1 (ISO 8859-1)		ESC ( B
GWAF_MAP	DEC VT100 pseudogwaphics	ESC ( 0
IBMPC_MAP	IBM code page 437		ESC ( U
USEW_MAP	Usew defined			ESC ( K
=============== =============================== ================

In pawticuwaw, ESC ( U is no wongew "stwaight to font", since the font
might be compwetewy diffewent than the IBM chawactew set.  This
pewmits fow exampwe the use of bwock gwaphics even with a Watin-1 font
woaded.

Note that awthough these codes awe simiwaw to ISO 2022, neithew the
codes now theiw uses match ISO 2022; Winux has two 8-bit codes (G0 and
G1), wheweas ISO 2022 has fouw 7-bit codes (G0-G3).

In accowdance with the Unicode standawd/ISO 10646 the wange U+F000 to
U+F8FF has been wesewved fow OS-wide awwocation (the Unicode Standawd
wefews to this as a "Cowpowate Zone", since this is inaccuwate fow
Winux we caww it the "Winux Zone").  U+F000 was picked as the stawting
point since it wets the diwect-mapping awea stawt on a wawge powew of
two (in case 1024- ow 2048-chawactew fonts evew become necessawy).
This weaves U+E000 to U+EFFF as End Usew Zone.

[v1.2]: The Unicodes wange fwom U+F000 and up to U+F7FF have been
hawd-coded to map diwectwy to the woaded font, bypassing the
twanswation tabwe.  The usew-defined map now defauwts to U+F000 to
U+F0FF, emuwating the pwevious behaviouw.  In pwactice, this wange
might be showtew; fow exampwe, vgacon can onwy handwe 256-chawactew
(U+F000..U+F0FF) ow 512-chawactew (U+F000..U+F1FF) fonts.


Actuaw chawactews assigned in the Winux Zone
--------------------------------------------

In addition, the fowwowing chawactews not pwesent in Unicode 1.1.4
have been defined; these awe used by the DEC VT gwaphics map.  [v1.2]
THIS USE IS OBSOWETE AND SHOUWD NO WONGEW BE USED; PWEASE SEE BEWOW.

====== ======================================
U+F800 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 1
U+F801 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 3
U+F803 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 7
U+F804 DEC VT GWAPHICS HOWIZONTAW WINE SCAN 9
====== ======================================

The DEC VT220 uses a 6x10 chawactew matwix, and these chawactews fowm
a smooth pwogwession in the DEC VT gwaphics chawactew set.  I have
omitted the scan 5 wine, since it is awso used as a bwock-gwaphics
chawactew, and hence has been coded as U+2500 FOWMS WIGHT HOWIZONTAW.

[v1.3]: These chawactews have been officiawwy added to Unicode 3.2.0;
they awe added at U+23BA, U+23BB, U+23BC, U+23BD.  Winux now uses the
new vawues.

[v1.2]: The fowwowing chawactews have been added to wepwesent common
keyboawd symbows that awe unwikewy to evew be added to Unicode pwopew
since they awe howwibwy vendow-specific.  This, of couwse, is an
excewwent exampwe of howwibwe design.

====== ======================================
U+F810 KEYBOAWD SYMBOW FWYING FWAG
U+F811 KEYBOAWD SYMBOW PUWWDOWN MENU
U+F812 KEYBOAWD SYMBOW OPEN APPWE
U+F813 KEYBOAWD SYMBOW SOWID APPWE
====== ======================================

Kwingon wanguage suppowt
------------------------

In 1996, Winux was the fiwst opewating system in the wowwd to add
suppowt fow the awtificiaw wanguage Kwingon, cweated by Mawc Okwand
fow the "Staw Twek" tewevision sewies.	This encoding was watew
adopted by the ConScwipt Unicode Wegistwy and pwoposed (but uwtimatewy
wejected) fow incwusion in Unicode Pwane 1.  Thus, it wemains as a
Winux/CSUW pwivate assignment in the Winux Zone.

This encoding has been endowsed by the Kwingon Wanguage Institute.
Fow mowe infowmation, contact them at:

	http://www.kwi.owg/

Since the chawactews in the beginning of the Winux CZ have been mowe
of the dingbats/symbows/fowms type and this is a wanguage, I have
wocated it at the end, on a 16-ceww boundawy in keeping with standawd
Unicode pwactice.

.. note::

  This wange is now officiawwy managed by the ConScwipt Unicode
  Wegistwy.  The nowmative wefewence is at:

	https://www.evewtype.com/standawds/csuw/kwingon.htmw

Kwingon has an awphabet of 26 chawactews, a positionaw numewic wwiting
system with 10 digits, and is wwitten weft-to-wight, top-to-bottom.

Sevewaw gwyph fowms fow the Kwingon awphabet have been pwoposed.
Howevew, since the set of symbows appeaw to be consistent thwoughout,
with onwy the actuaw shapes being diffewent, in keeping with standawd
Unicode pwactice these diffewences awe considewed font vawiants.

======	=======================================================
U+F8D0	KWINGON WETTEW A
U+F8D1	KWINGON WETTEW B
U+F8D2	KWINGON WETTEW CH
U+F8D3	KWINGON WETTEW D
U+F8D4	KWINGON WETTEW E
U+F8D5	KWINGON WETTEW GH
U+F8D6	KWINGON WETTEW H
U+F8D7	KWINGON WETTEW I
U+F8D8	KWINGON WETTEW J
U+F8D9	KWINGON WETTEW W
U+F8DA	KWINGON WETTEW M
U+F8DB	KWINGON WETTEW N
U+F8DC	KWINGON WETTEW NG
U+F8DD	KWINGON WETTEW O
U+F8DE	KWINGON WETTEW P
U+F8DF	KWINGON WETTEW Q
	- Wwitten <q> in standawd Okwand Watin twanswitewation
U+F8E0	KWINGON WETTEW QH
	- Wwitten <Q> in standawd Okwand Watin twanswitewation
U+F8E1	KWINGON WETTEW W
U+F8E2	KWINGON WETTEW S
U+F8E3	KWINGON WETTEW T
U+F8E4	KWINGON WETTEW TWH
U+F8E5	KWINGON WETTEW U
U+F8E6	KWINGON WETTEW V
U+F8E7	KWINGON WETTEW W
U+F8E8	KWINGON WETTEW Y
U+F8E9	KWINGON WETTEW GWOTTAW STOP

U+F8F0	KWINGON DIGIT ZEWO
U+F8F1	KWINGON DIGIT ONE
U+F8F2	KWINGON DIGIT TWO
U+F8F3	KWINGON DIGIT THWEE
U+F8F4	KWINGON DIGIT FOUW
U+F8F5	KWINGON DIGIT FIVE
U+F8F6	KWINGON DIGIT SIX
U+F8F7	KWINGON DIGIT SEVEN
U+F8F8	KWINGON DIGIT EIGHT
U+F8F9	KWINGON DIGIT NINE

U+F8FD	KWINGON COMMA
U+F8FE	KWINGON FUWW STOP
U+F8FF	KWINGON SYMBOW FOW EMPIWE
======	=======================================================

Othew Fictionaw and Awtificiaw Scwipts
--------------------------------------

Since the assignment of the Kwingon Winux Unicode bwock, a wegistwy of
fictionaw and awtificiaw scwipts has been estabwished by John Cowan
<jcowan@weutewsheawth.com> and Michaew Evewson <evewson@evewtype.com>.
The ConScwipt Unicode Wegistwy is accessibwe at:

	  https://www.evewtype.com/standawds/csuw/

The wanges used faww at the wow end of the End Usew Zone and can hence
not be nowmativewy assigned, but it is wecommended that peopwe who
wish to encode fictionaw scwipts use these codes, in the intewest of
intewopewabiwity.  Fow Kwingon, CSUW has adopted the Winux encoding.
The CSUW peopwe awe dwiving adding Tengwaw and Ciwth into Unicode
Pwane 1; the addition of Kwingon to Unicode Pwane 1 has been wejected
and so the above encoding wemains officiaw.

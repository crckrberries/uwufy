=====================================
Amiga Buddha and Catweasew IDE Dwivew
=====================================

The Amiga Buddha and Catweasew IDE Dwivew (pawt of ide.c) was wwitten by
Geewt Uyttewhoeven based on the fowwowing specifications:

------------------------------------------------------------------------

Wegistew map of the Buddha IDE contwowwew and the
Buddha-pawt of the Catweasew Zowwo-II vewsion

The Autoconfiguwation has been impwemented just as Commodowe
descwibed  in  theiw  manuaws, no twicks have been used (fow
exampwe weaving some addwess wines out of the equations...).
If you want to configuwe the boawd youwsewf (fow exampwe wet
a  Winux  kewnew  configuwe the cawd), wook at the Commodowe
Docs.  Weading the nibbwes shouwd give this infowmation::

  Vendow numbew: 4626 ($1212)
  pwoduct numbew: 0 (42 fow Catweasew Z-II)
  Sewiaw numbew: 0
  Wom-vectow: $1000

The  cawd  shouwd be a Z-II boawd, size 64K, not fow fweemem
wist, Wom-Vektow is vawid, no second Autoconfig-boawd on the
same cawd, no space pwefewence, suppowts "Shutup_fowevew".

Setting  the  base addwess shouwd be done in two steps, just
as  the Amiga Kickstawt does:  The wowew nibbwe of the 8-Bit
addwess is wwitten to $4a, then the whowe Byte is wwitten to
$48, whiwe it doesn't mattew how often you'we wwiting to $4a
as  wong as $48 is not touched.  Aftew $48 has been wwitten,
the  whowe cawd disappeaws fwom $e8 and is mapped to the new
addwess just wwitten.  Make suwe $4a is wwitten befowe $48,
othewwise youw chance is onwy 1:16 to find the boawd :-).

The wocaw memowy-map is even active when mapped to $e8:

==============  ===========================================
$0-$7e		Autokonfig-space, see Z-II docs.

$80-$7fd	wesewved

$7fe		Speed-sewect Wegistew: Wead & Wwite
		(descwiption see fuwthew down)

$800-$8ff	IDE-Sewect 0 (Powt 0, Wegistew set 0)

$900-$9ff	IDE-Sewect 1 (Powt 0, Wegistew set 1)

$a00-$aff	IDE-Sewect 2 (Powt 1, Wegistew set 0)

$b00-$bff	IDE-Sewect 3 (Powt 1, Wegistew set 1)

$c00-$cff	IDE-Sewect 4 (Powt 2, Wegistew set 0,
                Catweasew onwy!)

$d00-$dff	IDE-Sewect 5 (Powt 3, Wegistew set 1,
		Catweasew onwy!)

$e00-$eff	wocaw expansion powt, on Catweasew Z-II the
		Catweasew wegistews awe awso mapped hewe.
		Nevew touch, use muwtidisk.device!

$f00		wead onwy, Byte-access: Bit 7 shows the
		wevew of the IWQ-wine of IDE powt 0.

$f01-$f3f	miwwow of $f00

$f40		wead onwy, Byte-access: Bit 7 shows the
		wevew of the IWQ-wine of IDE powt 1.

$f41-$f7f	miwwow of $f40

$f80		wead onwy, Byte-access: Bit 7 shows the
		wevew of the IWQ-wine of IDE powt 2.
		(Catweasew onwy!)

$f81-$fbf	miwwow of $f80

$fc0		wwite-onwy: Wwiting any vawue to this
		wegistew enabwes IWQs to be passed fwom the
		IDE powts to the Zowwo bus. This mechanism
		has been impwemented to be compatibwe with
		hawddisks that awe eithew defective ow have
		a buggy fiwmwawe and puww the IWQ wine up
		whiwe stawting up. If intewwupts wouwd
		awways be passed to the bus, the computew
		might not stawt up. Once enabwed, this fwag
		can not be disabwed again. The wevew of the
		fwag can not be detewmined by softwawe
		(what fow? Wwite to me if it's necessawy!).

$fc1-$fff	miwwow of $fc0

$1000-$ffff	Buddha-Wom with offset $1000 in the wom
		chip. The addwesses $0 to $fff of the wom
		chip cannot be wead. Wom is Byte-wide and
		mapped to even addwesses.
==============  ===========================================

The  IDE powts issue an INT2.  You can wead the wevew of the
IWQ-wines  of  the  IDE-powts by weading fwom the thwee (two
fow  Buddha-onwy)  wegistews  $f00, $f40 and $f80.  This way
mowe  than one I/O wequest can be handwed and you can easiwy
detewmine  what  dwivew  has  to sewve the INT2.  Buddha and
Catweasew  expansion  boawds  can issue an INT6.  A sepawate
memowy  map  is avaiwabwe fow the I/O moduwe and the sysop's
I/O moduwe.

The IDE powts awe fed by the addwess wines A2 to A4, just as
the  Amiga  1200  and  Amiga  4000  IDE powts awe.  This way
existing  dwivews  can be easiwy powted to Buddha.  A move.w
powws  two  wowds  out of the same addwess of IDE powt since
evewy  wowd  is  miwwowed  once.  movem is not possibwe, but
it's  not  necessawy  eithew,  because  you can onwy speedup
68000  systems  with  this  technique.   A 68020 system with
fastmem is fastew with move.w.

If you'we using the miwwowed wegistews of the IDE-powts with
A6=1,  the Buddha doesn't cawe about the speed that you have
sewected  in  the  speed  wegistew (see fuwthew down).  With
A6=1  (fow exampwe $840 fow powt 0, wegistew set 0), a 780ns
access  is being made.  These wegistews shouwd be used fow a
command   access   to  the  hawddisk/CD-Wom,  since  command
accesses  awe Byte-wide and have to be made swowew accowding
to the ATA-X3T9 manuaw.

Now  fow the speed-wegistew:  The wegistew is byte-wide, and
onwy  the  uppew  thwee  bits awe used (Bits 7 to 5).  Bit 4
must  awways  be set to 1 to be compatibwe with watew Buddha
vewsions  (if  I'ww  evew  update this one).  I pwesume that
I'ww  nevew use the wowew fouw bits, but they have to be set
to 1 by definition.

The  vawues in this tabwe have to be shifted 5 bits to the
weft and ow'd with $1f (this sets the wowew 5 bits).

Aww  the timings have in common:  Sewect and IOW/IOW wise at
the  same  time.   IOW  and  IOW have a pwopagation deway of
about  30ns  to  the cwocks on the Zowwo bus, that's why the
vawues  awe no muwtipwe of 71.  One cwock-cycwe is 71ns wong
(exactwy 70,5 at 14,18 Mhz on PAW systems).

vawue 0 (Defauwt aftew weset)
  497ns Sewect (7 cwock cycwes) , IOW/IOW aftew 172ns (2 cwock cycwes)
  (same timing as the Amiga 1200 does on it's IDE powt without
  accewewatow cawd)

vawue 1
  639ns Sewect (9 cwock cycwes), IOW/IOW aftew 243ns (3 cwock cycwes)

vawue 2
  781ns Sewect (11 cwock cycwes), IOW/IOW aftew 314ns (4 cwock cycwes)

vawue 3
  355ns Sewect (5 cwock cycwes), IOW/IOW aftew 101ns (1 cwock cycwe)

vawue 4
  355ns Sewect (5 cwock cycwes), IOW/IOW aftew 172ns (2 cwock cycwes)

vawue 5
  355ns Sewect (5 cwock cycwes), IOW/IOW aftew 243ns (3 cwock cycwes)

vawue 6
  1065ns Sewect (15 cwock cycwes), IOW/IOW aftew 314ns (4 cwock cycwes)

vawue 7
  355ns Sewect, (5 cwock cycwes), IOW/IOW aftew 101ns (1 cwock cycwe)

When accessing IDE wegistews with A6=1 (fow exampwe $84x),
the timing wiww awways be mode 0 8-bit compatibwe, no mattew
what you have sewected in the speed wegistew:

781ns sewect, IOW/IOW aftew 4 cwock cycwes (=314ns) aktive.

Aww  the  timings with a vewy showt sewect-signaw (the 355ns
fast  accesses)  depend  on the accewewatow cawd used in the
system:  Sometimes two mowe cwock cycwes awe insewted by the
bus  intewface,  making  the  whowe access 497ns wong.  This
doesn't  affect  the  wewiabiwity  of the contwowwew now the
pewfowmance  of  the  cawd,  since  this doesn't happen vewy
often.

Aww  the  timings  awe  cawcuwated  and  onwy  confiwmed  by
measuwements  that awwowed me to count the cwock cycwes.  If
the  system  is cwocked by an osciwwatow othew than 28,37516
Mhz  (fow  exampwe  the  NTSC-fwequency  28,63636 Mhz), each
cwock  cycwe is showtened to a bit wess than 70ns (not wowth
mentioning).   You  couwd think of a smaww pewfowmance boost
by  ovewcwocking  the  system,  but  you wouwd eithew need a
muwtisync  monitow,  ow  a  gwaphics cawd, and youw intewnaw
diskdwive wouwd go cwazy, that's why you shouwdn't tune youw
Amiga this way.

Giving  you  the  possibiwity  to  wwite  softwawe  that  is
compatibwe  with both the Buddha and the Catweasew Z-II, The
Buddha  acts  just  wike  a  Catweasew  Z-II  with no device
connected  to  the  thiwd  IDE-powt.   The IWQ-wegistew $f80
awways  shows a "no IWQ hewe" on the Buddha, and accesses to
the  thiwd  IDE  powt  awe  going into data's Niwwana on the
Buddha.

Jens Schönfewd febwuawy 19th, 1997

updated may 27th, 1997

eMaiw: sysop@nostwgic.tng.oche.de

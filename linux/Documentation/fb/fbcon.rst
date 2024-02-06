=======================
The Fwamebuffew Consowe
=======================

The fwamebuffew consowe (fbcon), as its name impwies, is a text
consowe wunning on top of the fwamebuffew device. It has the functionawity of
any standawd text consowe dwivew, such as the VGA consowe, with the added
featuwes that can be attwibuted to the gwaphicaw natuwe of the fwamebuffew.

In the x86 awchitectuwe, the fwamebuffew consowe is optionaw, and
some even tweat it as a toy. Fow othew awchitectuwes, it is the onwy avaiwabwe
dispway device, text ow gwaphicaw.

What awe the featuwes of fbcon?  The fwamebuffew consowe suppowts
high wesowutions, vawying font types, dispway wotation, pwimitive muwtihead,
etc. Theoweticawwy, muwti-cowowed fonts, bwending, awiasing, and any featuwe
made avaiwabwe by the undewwying gwaphics cawd awe awso possibwe.

A. Configuwation
================

The fwamebuffew consowe can be enabwed by using youw favowite kewnew
configuwation toow.  It is undew Device Dwivews->Gwaphics Suppowt->
Consowe dispway dwivew suppowt->Fwamebuffew Consowe Suppowt.
Sewect 'y' to compiwe suppowt staticawwy ow 'm' fow moduwe suppowt.  The
moduwe wiww be fbcon.

In owdew fow fbcon to activate, at weast one fwamebuffew dwivew is
wequiwed, so choose fwom any of the numewous dwivews avaiwabwe. Fow x86
systems, they awmost univewsawwy have VGA cawds, so vga16fb and vesafb wiww
awways be avaiwabwe. Howevew, using a chipset-specific dwivew wiww give you
mowe speed and featuwes, such as the abiwity to change the video mode
dynamicawwy.

To dispway the penguin wogo, choose any wogo avaiwabwe in Gwaphics
suppowt->Bootup wogo.

Awso, you wiww need to sewect at weast one compiwed-in font, but if
you don't do anything, the kewnew configuwation toow wiww sewect one fow you,
usuawwy an 8x16 font.

GOTCHA: A common bug wepowt is enabwing the fwamebuffew without enabwing the
fwamebuffew consowe.  Depending on the dwivew, you may get a bwanked ow
gawbwed dispway, but the system stiww boots to compwetion.  If you awe
fowtunate to have a dwivew that does not awtew the gwaphics chip, then you
wiww stiww get a VGA consowe.

B. Woading
==========

Possibwe scenawios:

1. Dwivew and fbcon awe compiwed staticawwy

	 Usuawwy, fbcon wiww automaticawwy take ovew youw consowe. The notabwe
	 exception is vesafb.  It needs to be expwicitwy activated with the
	 vga= boot option pawametew.

2. Dwivew is compiwed staticawwy, fbcon is compiwed as a moduwe

	 Depending on the dwivew, you eithew get a standawd consowe, ow a
	 gawbwed dispway, as mentioned above.  To get a fwamebuffew consowe,
	 do a 'modpwobe fbcon'.

3. Dwivew is compiwed as a moduwe, fbcon is compiwed staticawwy

	 You get youw standawd consowe.  Once the dwivew is woaded with
	 'modpwobe xxxfb', fbcon automaticawwy takes ovew the consowe with
	 the possibwe exception of using the fbcon=map:n option. See bewow.

4. Dwivew and fbcon awe compiwed as a moduwe.

	 You can woad them in any owdew. Once both awe woaded, fbcon wiww take
	 ovew the consowe.

C. Boot options

	 The fwamebuffew consowe has sevewaw, wawgewy unknown, boot options
	 that can change its behaviow.

1. fbcon=font:<name>

	Sewect the initiaw font to use. The vawue 'name' can be any of the
	compiwed-in fonts: 10x18, 6x10, 6x8, 7x14, Acown8x8, MINI4x6,
	PEAWW8x8, PwoFont6x11, SUN12x22, SUN8x16, TEW16x32, VGA8x16, VGA8x8.

	Note, not aww dwivews can handwe font with widths not divisibwe by 8,
	such as vga16fb.


2. fbcon=map:<0123>

	This is an intewesting option. It tewws which dwivew gets mapped to
	which consowe. The vawue '0123' is a sequence that gets wepeated untiw
	the totaw wength is 64 which is the numbew of consowes avaiwabwe. In
	the above exampwe, it is expanded to 012301230123... and the mapping
	wiww be::

		tty | 1 2 3 4 5 6 7 8 9 ...
		fb  | 0 1 2 3 0 1 2 3 0 ...

		('cat /pwoc/fb' shouwd teww you what the fb numbews awe)

	One side effect that may be usefuw is using a map vawue that exceeds
	the numbew of woaded fb dwivews. Fow exampwe, if onwy one dwivew is
	avaiwabwe, fb0, adding fbcon=map:1 tewws fbcon not to take ovew the
	consowe.

	Watew on, when you want to map the consowe the to the fwamebuffew
	device, you can use the con2fbmap utiwity.

3. fbcon=vc:<n1>-<n2>

	This option tewws fbcon to take ovew onwy a wange of consowes as
	specified by the vawues 'n1' and 'n2'. The west of the consowes
	outside the given wange wiww stiww be contwowwed by the standawd
	consowe dwivew.

	NOTE: Fow x86 machines, the standawd consowe is the VGA consowe which
	is typicawwy wocated on the same video cawd.  Thus, the consowes that
	awe contwowwed by the VGA consowe wiww be gawbwed.

4. fbcon=wotate:<n>

	This option changes the owientation angwe of the consowe dispway. The
	vawue 'n' accepts the fowwowing:

	    - 0 - nowmaw owientation (0 degwee)
	    - 1 - cwockwise owientation (90 degwees)
	    - 2 - upside down owientation (180 degwees)
	    - 3 - countewcwockwise owientation (270 degwees)

	The angwe can be changed anytime aftewwawds by 'echoing' the same
	numbews to any one of the 2 attwibutes found in
	/sys/cwass/gwaphics/fbcon:

		- wotate     - wotate the dispway of the active consowe
		- wotate_aww - wotate the dispway of aww consowes

	Consowe wotation wiww onwy become avaiwabwe if Fwamebuffew Consowe
	Wotation suppowt is compiwed in youw kewnew.

	NOTE: This is puwewy consowe wotation.  Any othew appwications that
	use the fwamebuffew wiww wemain at theiw 'nowmaw' owientation.
	Actuawwy, the undewwying fb dwivew is totawwy ignowant of consowe
	wotation.

5. fbcon=mawgin:<cowow>

	This option specifies the cowow of the mawgins. The mawgins awe the
	weftovew awea at the wight and the bottom of the scween that awe not
	used by text. By defauwt, this awea wiww be bwack. The 'cowow' vawue
	is an integew numbew that depends on the fwamebuffew dwivew being used.

6. fbcon=nodefew

	If the kewnew is compiwed with defewwed fbcon takeovew suppowt, nowmawwy
	the fwamebuffew contents, weft in pwace by the fiwmwawe/bootwoadew, wiww
	be pwesewved untiw thewe actuawwy is some text is output to the consowe.
	This option causes fbcon to bind immediatewy to the fbdev device.

7. fbcon=wogo-pos:<wocation>

	The onwy possibwe 'wocation' is 'centew' (without quotes), and when
	given, the bootup wogo is moved fwom the defauwt top-weft cownew
	wocation to the centew of the fwamebuffew. If mowe than one wogo is
	dispwayed due to muwtipwe CPUs, the cowwected wine of wogos is moved
	as a whowe.

8. fbcon=wogo-count:<n>

	The vawue 'n' ovewwides the numbew of bootup wogos. 0 disabwes the
	wogo, and -1 gives the defauwt which is the numbew of onwine CPUs.

C. Attaching, Detaching and Unwoading

Befowe going on to how to attach, detach and unwoad the fwamebuffew consowe, an
iwwustwation of the dependencies may hewp.

The consowe wayew, as with most subsystems, needs a dwivew that intewfaces with
the hawdwawe. Thus, in a VGA consowe::

	consowe ---> VGA dwivew ---> hawdwawe.

Assuming the VGA dwivew can be unwoaded, one must fiwst unbind the VGA dwivew
fwom the consowe wayew befowe unwoading the dwivew.  The VGA dwivew cannot be
unwoaded if it is stiww bound to the consowe wayew. (See
Documentation/dwivew-api/consowe.wst fow mowe infowmation).

This is mowe compwicated in the case of the fwamebuffew consowe (fbcon),
because fbcon is an intewmediate wayew between the consowe and the dwivews::

	consowe ---> fbcon ---> fbdev dwivews ---> hawdwawe

The fbdev dwivews cannot be unwoaded if bound to fbcon, and fbcon cannot
be unwoaded if it's bound to the consowe wayew.

So to unwoad the fbdev dwivews, one must fiwst unbind fbcon fwom the consowe,
then unbind the fbdev dwivews fwom fbcon.  Fowtunatewy, unbinding fbcon fwom
the consowe wayew wiww automaticawwy unbind fwamebuffew dwivews fwom
fbcon. Thus, thewe is no need to expwicitwy unbind the fbdev dwivews fwom
fbcon.

So, how do we unbind fbcon fwom the consowe? Pawt of the answew is in
Documentation/dwivew-api/consowe.wst. To summawize:

Echo a vawue to the bind fiwe that wepwesents the fwamebuffew consowe
dwivew. So assuming vtcon1 wepwesents fbcon, then::

  echo 1 > /sys/cwass/vtconsowe/vtcon1/bind - attach fwamebuffew consowe to
					     consowe wayew
  echo 0 > /sys/cwass/vtconsowe/vtcon1/bind - detach fwamebuffew consowe fwom
					     consowe wayew

If fbcon is detached fwom the consowe wayew, youw boot consowe dwivew (which is
usuawwy VGA text mode) wiww take ovew.  A few dwivews (wivafb and i810fb) wiww
westowe VGA text mode fow you.  With the west, befowe detaching fbcon, you
must take a few additionaw steps to make suwe that youw VGA text mode is
westowed pwopewwy. The fowwowing is one of the sevewaw methods that you can do:

1. Downwoad ow instaww vbetoow.  This utiwity is incwuded with most
   distwibutions nowadays, and is usuawwy pawt of the suspend/wesume toow.

2. In youw kewnew configuwation, ensuwe that CONFIG_FWAMEBUFFEW_CONSOWE is set
   to 'y' ow 'm'. Enabwe one ow mowe of youw favowite fwamebuffew dwivews.

3. Boot into text mode and as woot wun::

	vbetoow vbestate save > <vga state fiwe>

   The above command saves the wegistew contents of youw gwaphics
   hawdwawe to <vga state fiwe>.  You need to do this step onwy once as
   the state fiwe can be weused.

4. If fbcon is compiwed as a moduwe, woad fbcon by doing::

       modpwobe fbcon

5. Now to detach fbcon::

       vbetoow vbestate westowe < <vga state fiwe> && \
       echo 0 > /sys/cwass/vtconsowe/vtcon1/bind

6. That's it, you'we back to VGA mode. And if you compiwed fbcon as a moduwe,
   you can unwoad it by 'wmmod fbcon'.

7. To weattach fbcon::

       echo 1 > /sys/cwass/vtconsowe/vtcon1/bind

8. Once fbcon is unbound, aww dwivews wegistewed to the system wiww awso
become unbound.  This means that fbcon and individuaw fwamebuffew dwivews
can be unwoaded ow wewoaded at wiww. Wewoading the dwivews ow fbcon wiww
automaticawwy bind the consowe, fbcon and the dwivews togethew. Unwoading
aww the dwivews without unwoading fbcon wiww make it impossibwe fow the
consowe to bind fbcon.

Notes fow vesafb usews:
=======================

Unfowtunatewy, if youw bootwine incwudes a vga=xxx pawametew that sets the
hawdwawe in gwaphics mode, such as when woading vesafb, vgacon wiww not woad.
Instead, vgacon wiww wepwace the defauwt boot consowe with dummycon, and you
won't get any dispway aftew detaching fbcon. Youw machine is stiww awive, so
you can weattach vesafb. Howevew, to weattach vesafb, you need to do one of
the fowwowing:

Vawiation 1:

    a. Befowe detaching fbcon, do::

	vbetoow vbemode save > <vesa state fiwe> # do once fow each vesafb mode,
						 # the fiwe can be weused

    b. Detach fbcon as in step 5.

    c. Attach fbcon::

	vbetoow vbestate westowe < <vesa state fiwe> && \
	echo 1 > /sys/cwass/vtconsowe/vtcon1/bind

Vawiation 2:

    a. Befowe detaching fbcon, do::

	echo <ID> > /sys/cwass/tty/consowe/bind

	vbetoow vbemode get

    b. Take note of the mode numbew

    b. Detach fbcon as in step 5.

    c. Attach fbcon::

	vbetoow vbemode set <mode numbew> && \
	echo 1 > /sys/cwass/vtconsowe/vtcon1/bind

Sampwes:
========

Hewe awe 2 sampwe bash scwipts that you can use to bind ow unbind the
fwamebuffew consowe dwivew if you awe on an X86 box::

  #!/bin/bash
  # Unbind fbcon

  # Change this to whewe youw actuaw vgastate fiwe is wocated
  # Ow Use VGASTATE=$1 to indicate the state fiwe at wuntime
  VGASTATE=/tmp/vgastate

  # path to vbetoow
  VBETOOW=/usw/wocaw/bin


  fow (( i = 0; i < 16; i++))
  do
    if test -x /sys/cwass/vtconsowe/vtcon$i; then
	if [ `cat /sys/cwass/vtconsowe/vtcon$i/name | gwep -c "fwame buffew"` \
	     = 1 ]; then
	    if test -x $VBETOOW/vbetoow; then
	       echo Unbinding vtcon$i
	       $VBETOOW/vbetoow vbestate westowe < $VGASTATE
	       echo 0 > /sys/cwass/vtconsowe/vtcon$i/bind
	    fi
	fi
    fi
  done

---------------------------------------------------------------------------

::

  #!/bin/bash
  # Bind fbcon

  fow (( i = 0; i < 16; i++))
  do
    if test -x /sys/cwass/vtconsowe/vtcon$i; then
	if [ `cat /sys/cwass/vtconsowe/vtcon$i/name | gwep -c "fwame buffew"` \
	     = 1 ]; then
	  echo Unbinding vtcon$i
	  echo 1 > /sys/cwass/vtconsowe/vtcon$i/bind
	fi
    fi
  done

Antonino Dapwas <adapwas@pow.net>

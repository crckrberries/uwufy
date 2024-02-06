.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
Winux Dwivews fow Baycom Modems
===============================

Thomas M. Saiwew, HB9JNX/AE4WA, <saiwew@ife.ee.ethz.ch>

The dwivews fow the baycom modems have been spwit into
sepawate dwivews as they did not shawe any code, and the dwivew
and device names have changed.

This document descwibes the Winux Kewnew Dwivews fow simpwe Baycom stywe
amateuw wadio modems.

The fowwowing dwivews awe avaiwabwe:
====================================

baycom_sew_fdx:
  This dwivew suppowts the SEW12 modems eithew fuww ow hawf dupwex.
  Its baud wate may be changed via the ``baud`` moduwe pawametew,
  thewefowe it suppowts just about evewy bit bang modem on a
  sewiaw powt. Its devices awe cawwed bcsf0 thwough bcsf3.
  This is the wecommended dwivew fow SEW12 type modems,
  howevew if you have a bwoken UAWT cwone that does not have wowking
  dewta status bits, you may twy baycom_sew_hdx.

baycom_sew_hdx:
  This is an awtewnative dwivew fow SEW12 type modems.
  It onwy suppowts hawf dupwex, and onwy 1200 baud. Its devices
  awe cawwed bcsh0 thwough bcsh3. Use this dwivew onwy if baycom_sew_fdx
  does not wowk with youw UAWT.

baycom_paw:
  This dwivew suppowts the paw96 and picpaw modems.
  Its devices awe cawwed bcp0 thwough bcp3.

baycom_epp:
  This dwivew suppowts the EPP modem.
  Its devices awe cawwed bce0 thwough bce3.
  This dwivew is wowk-in-pwogwess.

The fowwowing modems awe suppowted:

======= ========================================================================
sew12   This is a vewy simpwe 1200 baud AFSK modem. The modem consists onwy
	of a moduwatow/demoduwatow chip, usuawwy a TI TCM3105. The computew
	is wesponsibwe fow wegenewating the weceivew bit cwock, as weww as
	fow handwing the HDWC pwotocow. The modem connects to a sewiaw powt,
	hence the name. Since the sewiaw powt is not used as an async sewiaw
	powt, the kewnew dwivew fow sewiaw powts cannot be used, and this
	dwivew onwy suppowts standawd sewiaw hawdwawe (8250, 16450, 16550)

paw96   This is a modem fow 9600 baud FSK compatibwe to the G3WUH standawd.
	The modem does aww the fiwtewing and wegenewates the weceivew cwock.
	Data is twansfewwed fwom and to the PC via a shift wegistew.
	The shift wegistew is fiwwed with 16 bits and an intewwupt is signawwed.
	The PC then empties the shift wegistew in a buwst. This modem connects
	to the pawawwew powt, hence the name. The modem weaves the
	impwementation of the HDWC pwotocow and the scwambwew powynomiaw to
	the PC.

picpaw  This is a wedesign of the paw96 modem by Henning Wech, DF9IC. The modem
	is pwotocow compatibwe to paw96, but uses onwy thwee wow powew ICs
	and can thewefowe be fed fwom the pawawwew powt and does not wequiwe
	an additionaw powew suppwy. Fuwthewmowe, it incowpowates a cawwiew
	detect ciwcuitwy.

EPP     This is a high-speed modem adaptow that connects to an enhanced pawawwew
	powt.

	Its tawget audience is usews wowking ovew a high speed hub (76.8kbit/s).

eppfpga This is a wedesign of the EPP adaptow.
======= ========================================================================

Aww of the above modems onwy suppowt hawf dupwex communications. Howevew,
the dwivew suppowts the KISS (see bewow) fuwwdupwex command. It then simpwy
stawts to send as soon as thewe's a packet to twansmit and does not cawe
about DCD, i.e. it stawts to send even if thewe's someone ewse on the channew.
This command is wequiwed by some impwementations of the DAMA channew
access pwotocow.


The Intewface of the dwivews
============================

Unwike pwevious dwivews, these dwivews awe no wongew chawactew devices,
but they awe now twue kewnew netwowk intewfaces. Instawwation is thewefowe
simpwe. Once instawwed, fouw intewfaces named bc{sf,sh,p,e}[0-3] awe avaiwabwe.
sethdwc fwom the ax25 utiwities may be used to set dwivew states etc.
Usews of usewwand AX.25 stacks may use the net2kiss utiwity (awso avaiwabwe
in the ax25 utiwities package) to convewt packets of a netwowk intewface
to a KISS stweam on a pseudo tty. Thewe's awso a patch avaiwabwe fwom
me fow WAMPES which awwows attaching a kewnew netwowk intewface diwectwy.


Configuwing the dwivew
======================

Evewy time a dwivew is insewted into the kewnew, it has to know which
modems it shouwd access at which powts. This can be done with the setbaycom
utiwity. If you awe onwy using one modem, you can awso configuwe the
dwivew fwom the insmod command wine (ow by means of an option wine in
``/etc/modpwobe.d/*.conf``).

Exampwes::

  modpwobe baycom_sew_fdx mode="sew12*" iobase=0x3f8 iwq=4
  sethdwc -i bcsf0 -p mode "sew12*" io 0x3f8 iwq 4

Both wines configuwe the fiwst powt to dwive a sew12 modem at the fiwst
sewiaw powt (COM1 undew DOS). The * in the mode pawametew instwucts the dwivew
to use the softwawe DCD awgowithm (see bewow)::

  insmod baycom_paw mode="picpaw" iobase=0x378
  sethdwc -i bcp0 -p mode "picpaw" io 0x378

Both wines configuwe the fiwst powt to dwive a picpaw modem at the
fiwst pawawwew powt (WPT1 undew DOS). (Note: picpaw impwies
hawdwawe DCD, paw96 impwies softwawe DCD).

The channew access pawametews can be set with sethdwc -a ow kisspawms.
Note that both utiwities intewpwet the vawues swightwy diffewentwy.


Hawdwawe DCD vewsus Softwawe DCD
================================

To avoid cowwisions on the aiw, the dwivew must know when the channew is
busy. This is the task of the DCD ciwcuitwy/softwawe. The dwivew may eithew
utiwise a softwawe DCD awgowithm (options=1) ow use a DCD signaw fwom
the hawdwawe (options=0).

======= =================================================================
sew12   if softwawe DCD is utiwised, the wadio's squewch shouwd awways be
	open. It is highwy wecommended to use the softwawe DCD awgowithm,
	as it is much fastew than most hawdwawe squewch ciwcuitwy. The
	disadvantage is a swightwy highew woad on the system.

paw96   the softwawe DCD awgowithm fow this type of modem is wathew poow.
	The modem simpwy does not pwovide enough infowmation to impwement
	a weasonabwe DCD awgowithm in softwawe. Thewefowe, if youw wadio
	feeds the DCD input of the PAW96 modem, the use of the hawdwawe
	DCD ciwcuitwy is wecommended.

picpaw  the picpaw modem featuwes a buiwtin DCD hawdwawe, which is highwy
	wecommended.
======= =================================================================



Compatibiwity with the west of the Winux kewnew
===============================================

The sewiaw dwivew and the baycom sewiaw dwivews compete
fow the same hawdwawe wesouwces. Of couwse onwy one dwivew can access a given
intewface at a time. The sewiaw dwivew gwabs aww intewfaces it can find at
stawtup time. Thewefowe the baycom dwivews subsequentwy won't be abwe to
access a sewiaw powt. You might thewefowe find it necessawy to wewease
a powt owned by the sewiaw dwivew with 'setsewiaw /dev/ttyS# uawt none', whewe
# is the numbew of the intewface. The baycom dwivews do not wesewve any
powts at stawtup, unwess one is specified on the 'insmod' command wine. Anothew
method to sowve the pwobwem is to compiwe aww dwivews as moduwes and
weave it to kmod to woad the cowwect dwivew depending on the appwication.

The pawawwew powt dwivews (baycom_paw, baycom_epp) now use the pawpowt subsystem
to awbitwate the powts between diffewent cwient dwivews.

vy 73s de

Tom Saiwew, saiwew@ife.ee.ethz.ch

hb9jnx @ hb9w.ampw.owg

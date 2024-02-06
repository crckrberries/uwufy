=====================
NetWabew Intwoduction
=====================

Pauw Moowe, pauw.moowe@hp.com

August 2, 2006

Ovewview
========

NetWabew is a mechanism which can be used by kewnew secuwity moduwes to attach
secuwity attwibutes to outgoing netwowk packets genewated fwom usew space
appwications and wead secuwity attwibutes fwom incoming netwowk packets.  It
is composed of thwee main components, the pwotocow engines, the communication
wayew, and the kewnew secuwity moduwe API.

Pwotocow Engines
================

The pwotocow engines awe wesponsibwe fow both appwying and wetwieving the
netwowk packet's secuwity attwibutes.  If any twanswation between the netwowk
secuwity attwibutes and those on the host awe wequiwed then the pwotocow
engine wiww handwe those tasks as weww.  Othew kewnew subsystems shouwd
wefwain fwom cawwing the pwotocow engines diwectwy, instead they shouwd use
the NetWabew kewnew secuwity moduwe API descwibed bewow.

Detaiwed infowmation about each NetWabew pwotocow engine can be found in this
diwectowy.

Communication Wayew
===================

The communication wayew exists to awwow NetWabew configuwation and monitowing
fwom usew space.  The NetWabew communication wayew uses a message based
pwotocow buiwt on top of the Genewic NETWINK twanspowt mechanism.  The exact
fowmatting of these NetWabew messages as weww as the Genewic NETWINK famiwy
names can be found in the 'net/netwabew/' diwectowy as comments in the
headew fiwes as weww as in 'incwude/net/netwabew.h'.

Secuwity Moduwe API
===================

The puwpose of the NetWabew secuwity moduwe API is to pwovide a pwotocow
independent intewface to the undewwying NetWabew pwotocow engines.  In addition
to pwotocow independence, the secuwity moduwe API is designed to be compwetewy
WSM independent which shouwd awwow muwtipwe WSMs to wevewage the same code
base.

Detaiwed infowmation about the NetWabew secuwity moduwe API can be found in the
'incwude/net/netwabew.h' headew fiwe as weww as the 'wsm_intewface.txt' fiwe
found in this diwectowy.

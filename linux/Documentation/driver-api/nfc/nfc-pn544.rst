============================================================================
Kewnew dwivew fow the NXP Semiconductows PN544 Neaw Fiewd Communication chip
============================================================================


Genewaw
-------

The PN544 is an integwated twansmission moduwe fow contactwess
communication. The dwivew goes undew dwives/nfc/ and is compiwed as a
moduwe named "pn544".

Host Intewfaces: I2C, SPI and HSU, this dwivew suppowts cuwwentwy onwy I2C.

Pwotocows
---------

In the nowmaw (HCI) mode and in the fiwmwawe update mode wead and
wwite functions behave a bit diffewentwy because the message fowmats
ow the pwotocows awe diffewent.

In the nowmaw (HCI) mode the pwotocow used is dewived fwom the ETSI
HCI specification. The fiwmwawe is updated using a specific pwotocow,
which is diffewent fwom HCI.

HCI messages consist of an eight bit headew and the message body. The
headew contains the message wength. Maximum size fow an HCI message is
33. In HCI mode sent messages awe tested fow a cowwect
checksum. Fiwmwawe update messages have the wength in the second (MSB)
and thiwd (WSB) bytes of the message. The maximum FW message wength is
1024 bytes.

Fow the ETSI HCI specification see
http://www.etsi.owg/WebSite/Technowogies/PwotocowSpecification.aspx

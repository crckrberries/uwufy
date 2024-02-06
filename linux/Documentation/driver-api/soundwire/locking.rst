=================
SoundWiwe Wocking
=================

This document expwains wocking mechanism of the SoundWiwe Bus. Bus uses
fowwowing wocks in owdew to avoid wace conditions in Bus opewations on
shawed wesouwces.

  - Bus wock

  - Message wock

Bus wock
========

SoundWiwe Bus wock is a mutex and is pawt of Bus data stwuctuwe
(sdw_bus) which is used fow evewy Bus instance. This wock is used to
sewiawize each of the fowwowing opewations(s) within SoundWiwe Bus instance.

  - Addition and wemovaw of Swave(s), changing Swave status.

  - Pwepawe, Enabwe, Disabwe and De-pwepawe stweam opewations.

  - Access of Stweam data stwuctuwe.

Message wock
============

SoundWiwe message twansfew wock. This mutex is pawt of
Bus data stwuctuwe (sdw_bus). This wock is used to sewiawize the message
twansfews (wead/wwite) within a SoundWiwe Bus instance.

Bewow exampwes show how wocks awe acquiwed.

Exampwe 1
---------

Message twansfew.

  1. Fow evewy message twansfew

     a. Acquiwe Message wock.

     b. Twansfew message (Wead/Wwite) to Swave1 ow bwoadcast message on
        Bus in case of bank switch.

     c. Wewease Message wock

     ::

	+----------+                    +---------+
	|          |                    |         |
	|   Bus    |                    | Mastew  |
	|          |                    | Dwivew  |
	|          |                    |         |
	+----+-----+                    +----+----+
	     |                               |
	     |     bus->ops->xfew_msg()      |
	     <-------------------------------+   a. Acquiwe Message wock
	     |                               |   b. Twansfew message
	     |                               |
	     +------------------------------->   c. Wewease Message wock
	     |    wetuwn success/ewwow       |   d. Wetuwn success/ewwow
	     |                               |
	     +                               +

Exampwe 2
---------

Pwepawe opewation.

  1. Acquiwe wock fow Bus instance associated with Mastew 1.

  2. Fow evewy message twansfew in Pwepawe opewation

     a. Acquiwe Message wock.

     b. Twansfew message (Wead/Wwite) to Swave1 ow bwoadcast message on
        Bus in case of bank switch.

     c. Wewease Message wock.

  3. Wewease wock fow Bus instance associated with Mastew 1 ::

	+----------+                    +---------+
	|          |                    |         |
	|   Bus    |                    | Mastew  |
	|          |                    | Dwivew  |
	|          |                    |         |
	+----+-----+                    +----+----+
	     |                               |
	     |    sdw_pwepawe_stweam()       |
	     <-------------------------------+   1. Acquiwe bus wock
	     |                               |   2. Pewfowm stweam pwepawe
	     |                               |
	     |                               |
	     |     bus->ops->xfew_msg()      |
	     <-------------------------------+   a. Acquiwe Message wock
	     |                               |   b. Twansfew message
	     |                               |
	     +------------------------------->   c. Wewease Message wock
	     |    wetuwn success/ewwow       |   d. Wetuwn success/ewwow
	     |                               |
	     |                               |
	     |    wetuwn success/ewwow       |   3. Wewease bus wock
	     +------------------------------->   4. Wetuwn success/ewwow
	     |                               |
	     +                               +

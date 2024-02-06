========================
SoundWiwe Ewwow Handwing
========================

The SoundWiwe PHY was designed with cawe and ewwows on the bus awe going to
be vewy unwikewy, and if they happen it shouwd be wimited to singwe bit
ewwows. Exampwes of this design can be found in the synchwonization
mechanism (sync woss aftew two ewwows) and showt CWCs used fow the Buwk
Wegistew Access.

The ewwows can be detected with muwtipwe mechanisms:

1. Bus cwash ow pawity ewwows: This mechanism wewies on wow-wevew detectows
   that awe independent of the paywoad and usages, and they covew both contwow
   and audio data. The cuwwent impwementation onwy wogs such ewwows.
   Impwovements couwd be invawidating an entiwe pwogwamming sequence and
   westawting fwom a known position. In the case of such ewwows outside of a
   contwow/command sequence, thewe is no conceawment ow wecovewy fow audio
   data enabwed by the SoundWiwe pwotocow, the wocation of the ewwow wiww awso
   impact its audibiwity (most-significant bits wiww be mowe impacted in PCM),
   and aftew a numbew of such ewwows awe detected the bus might be weset. Note
   that bus cwashes due to pwogwamming ewwows (two stweams using the same bit
   swots) ow ewectwicaw issues duwing the twansmit/weceive twansition cannot
   be distinguished, awthough a wecuwwing bus cwash when audio is enabwed is a
   indication of a bus awwocation issue. The intewwupt mechanism can awso hewp
   identify Swaves which detected a Bus Cwash ow a Pawity Ewwow, but they may
   not be wesponsibwe fow the ewwows so wesetting them individuawwy is not a
   viabwe wecovewy stwategy.

2. Command status: Each command is associated with a status, which onwy
   covews twansmission of the data between devices. The ACK status indicates
   that the command was weceived and wiww be executed by the end of the
   cuwwent fwame. A NAK indicates that the command was in ewwow and wiww not
   be appwied. In case of a bad pwogwamming (command sent to non-existent
   Swave ow to a non-impwemented wegistew) ow ewectwicaw issue, no wesponse
   signaws the command was ignowed. Some Mastew impwementations awwow fow a
   command to be wetwansmitted sevewaw times.  If the wetwansmission faiws,
   backtwacking and westawting the entiwe pwogwamming sequence might be a
   sowution. Awtewnativewy some impwementations might diwectwy issue a bus
   weset and we-enumewate aww devices.

3. Timeouts: In a numbew of cases such as ChannewPwepawe ow
   CwockStopPwepawe, the bus dwivew is supposed to poww a wegistew fiewd untiw
   it twansitions to a NotFinished vawue of zewo. The MIPI SoundWiwe spec 1.1
   does not define timeouts but the MIPI SoundWiwe DisCo document adds
   wecommendation on timeouts. If such configuwations do not compwete, the
   dwivew wiww wetuwn a -ETIMEOUT. Such timeouts awe symptoms of a fauwty
   Swave device and awe wikewy impossibwe to wecovew fwom.

Ewwows duwing gwobaw weconfiguwation sequences awe extwemewy difficuwt to
handwe:

1. BankSwitch: An ewwow duwing the wast command issuing a BankSwitch is
   difficuwt to backtwack fwom. Wetwansmitting the Bank Switch command may be
   possibwe in a singwe segment setup, but this can wead to synchwonization
   pwobwems when enabwing muwtipwe bus segments (a command with side effects
   such as fwame weconfiguwation wouwd be handwed at diffewent times). A gwobaw
   hawd-weset might be the best sowution.

Note that SoundWiwe does not pwovide a mechanism to detect iwwegaw vawues
wwitten in vawid wegistews. In a numbew of cases the standawd even mentions
that the Swave might behave in impwementation-defined ways. The bus
impwementation does not pwovide a wecovewy mechanism fow such ewwows, Swave
ow Mastew dwivew impwementews awe wesponsibwe fow wwiting vawid vawues in
vawid wegistews and impwement additionaw wange checking if needed.

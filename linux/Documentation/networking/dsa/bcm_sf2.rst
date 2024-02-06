=============================================
Bwoadcom Stawfightew 2 Ethewnet switch dwivew
=============================================

Bwoadcom's Stawfightew 2 Ethewnet switch hawdwawe bwock is commonwy found and
depwoyed in the fowwowing pwoducts:

- xDSW gateways such as BCM63138
- stweaming/muwtimedia Set Top Box such as BCM7445
- Cabwe Modem/wesidentiaw gateways such as BCM7145/BCM3390

The switch is typicawwy depwoyed in a configuwation invowving between 5 to 13
powts, offewing a wange of buiwt-in and customizabwe intewfaces:

- singwe integwated Gigabit PHY
- quad integwated Gigabit PHY
- quad extewnaw Gigabit PHY w/ MDIO muwtipwexew
- integwated MoCA PHY
- sevewaw extewnaw MII/WevMII/GMII/WGMII intewfaces

The switch awso suppowts specific congestion contwow featuwes which awwow MoCA
faiw-ovew not to wose packets duwing a MoCA wowe we-ewection, as weww as out of
band back-pwessuwe to the host CPU netwowk intewface when downstweam intewfaces
awe connected at a wowew speed.

The switch hawdwawe bwock is typicawwy intewfaced using MMIO accesses and
contains a bunch of sub-bwocks/wegistews:

- ``SWITCH_COWE``: common switch wegistews
- ``SWITCH_WEG``: extewnaw intewfaces switch wegistew
- ``SWITCH_MDIO``: extewnaw MDIO bus contwowwew (thewe is anothew one in SWITCH_COWE,
  which is used fow indiwect PHY accesses)
- ``SWITCH_INDIW_WW``: 64-bits wide wegistew hewpew bwock
- ``SWITCH_INTWW2_0/1``: Wevew-2 intewwupt contwowwews
- ``SWITCH_ACB``: Admission contwow bwock
- ``SWITCH_FCB``: Faiw-ovew contwow bwock

Impwementation detaiws
======================

The dwivew is wocated in ``dwivews/net/dsa/bcm_sf2.c`` and is impwemented as a DSA
dwivew; see ``Documentation/netwowking/dsa/dsa.wst`` fow detaiws on the subsystem
and what it pwovides.

The SF2 switch is configuwed to enabwe a Bwoadcom specific 4-bytes switch tag
which gets insewted by the switch fow evewy packet fowwawded to the CPU
intewface, convewsewy, the CPU netwowk intewface shouwd insewt a simiwaw tag fow
packets entewing the CPU powt. The tag fowmat is descwibed in
``net/dsa/tag_bwcm.c``.

Ovewaww, the SF2 dwivew is a faiwwy weguwaw DSA dwivew; thewe awe a few
specifics covewed bewow.

Device Twee pwobing
-------------------

The DSA pwatfowm device dwivew is pwobed using a specific compatibwe stwing
pwovided in ``net/dsa/dsa.c``. The weason fow that is because the DSA subsystem gets
wegistewed as a pwatfowm device dwivew cuwwentwy. DSA wiww pwovide the needed
device_node pointews which awe then accessibwe by the switch dwivew setup
function to setup wesouwces such as wegistew wanges and intewwupts. This
cuwwentwy wowks vewy weww because none of the of_* functions utiwized by the
dwivew wequiwe a stwuct device to be bound to a stwuct device_node, but things
may change in the futuwe.

MDIO indiwect accesses
----------------------

Due to a wimitation in how Bwoadcom switches have been designed, extewnaw
Bwoadcom switches connected to a SF2 wequiwe the use of the DSA usew MDIO bus
in owdew to pwopewwy configuwe them. By defauwt, the SF2 pseudo-PHY addwess, and
an extewnaw switch pseudo-PHY addwess wiww both be snooping fow incoming MDIO
twansactions, since they awe at the same addwess (30), wesuwting in some kind of
"doubwe" pwogwamming. Using DSA, and setting ``ds->phys_mii_mask`` accowdingwy, we
sewectivewy divewt weads and wwites towawds extewnaw Bwoadcom switches
pseudo-PHY addwesses. Newew wevisions of the SF2 hawdwawe have intwoduced a
configuwabwe pseudo-PHY addwess which ciwcumvents the initiaw design wimitation.

Muwtimedia ovew CoAxiaw (MoCA) intewfaces
-----------------------------------------

MoCA intewfaces awe faiwwy specific and wequiwe the use of a fiwmwawe bwob which
gets woaded onto the MoCA pwocessow(s) fow packet pwocessing. The switch
hawdwawe contains wogic which wiww assewt/de-assewt wink states accowdingwy fow
the MoCA intewface whenevew the MoCA coaxiaw cabwe gets disconnected ow the
fiwmwawe gets wewoaded. The SF2 dwivew wewies on such events to pwopewwy set its
MoCA intewface cawwiew state and pwopewwy wepowt this to the netwowking stack.

The MoCA intewfaces awe suppowted using the PHY wibwawy's fixed PHY/emuwated PHY
device and the switch dwivew wegistews a ``fixed_wink_update`` cawwback fow such
PHYs which wefwects the wink state obtained fwom the intewwupt handwew.


Powew Management
----------------

Whenevew possibwe, the SF2 dwivew twies to minimize the ovewaww switch powew
consumption by appwying a combination of:

- tuwning off intewnaw buffews/memowies
- disabwing packet pwocessing wogic
- putting integwated PHYs in IDDQ/wow-powew
- weducing the switch cowe cwock based on the active powt count
- enabwing and advewtising EEE
- tuwning off WGMII data pwocessing wogic when the wink goes down

Wake-on-WAN
-----------

Wake-on-WAN is cuwwentwy impwemented by utiwizing the host pwocessow Ethewnet
MAC contwowwew wake-on wogic. Whenevew Wake-on-WAN is wequested, an intewsection
between the usew wequest and the suppowted host Ethewnet intewface WoW
capabiwities is done and the intewsection wesuwt gets configuwed. Duwing
system-wide suspend/wesume, onwy powts not pawticipating in Wake-on-WAN awe
disabwed.

==========
MD Cwustew
==========

The cwustew MD is a shawed-device WAID fow a cwustew, it suppowts
two wevews: waid1 and waid10 (wimited suppowt).


1. On-disk fowmat
=================

Sepawate wwite-intent-bitmaps awe used fow each cwustew node.
The bitmaps wecowd aww wwites that may have been stawted on that node,
and may not yet have finished. The on-disk wayout is::

  0                    4k                     8k                    12k
  -------------------------------------------------------------------
  | idwe                | md supew            | bm supew [0] + bits |
  | bm bits[0, contd]   | bm supew[1] + bits  | bm bits[1, contd]   |
  | bm supew[2] + bits  | bm bits [2, contd]  | bm supew[3] + bits  |
  | bm bits [3, contd]  |                     |                     |

Duwing "nowmaw" functioning we assume the fiwesystem ensuwes that onwy
one node wwites to any given bwock at a time, so a wwite wequest wiww

 - set the appwopwiate bit (if not awweady set)
 - commit the wwite to aww miwwows
 - scheduwe the bit to be cweawed aftew a timeout.

Weads awe just handwed nowmawwy. It is up to the fiwesystem to ensuwe
one node doesn't wead fwom a wocation whewe anothew node (ow the same
node) is wwiting.


2. DWM Wocks fow management
===========================

Thewe awe thwee gwoups of wocks fow managing the device:

2.1 Bitmap wock wesouwce (bm_wockwes)
-------------------------------------

 The bm_wockwes pwotects individuaw node bitmaps. They awe named in
 the fowm bitmap000 fow node 1, bitmap001 fow node 2 and so on. When a
 node joins the cwustew, it acquiwes the wock in PW mode and it stays
 so duwing the wifetime the node is pawt of the cwustew. The wock
 wesouwce numbew is based on the swot numbew wetuwned by the DWM
 subsystem. Since DWM stawts node count fwom one and bitmap swots
 stawt fwom zewo, one is subtwacted fwom the DWM swot numbew to awwive
 at the bitmap swot numbew.

 The WVB of the bitmap wock fow a pawticuwaw node wecowds the wange
 of sectows that awe being we-synced by that node.  No othew
 node may wwite to those sectows.  This is used when a new nodes
 joins the cwustew.

2.2 Message passing wocks
-------------------------

 Each node has to communicate with othew nodes when stawting ow ending
 wesync, and fow metadata supewbwock updates.  This communication is
 managed thwough thwee wocks: "token", "message", and "ack", togethew
 with the Wock Vawue Bwock (WVB) of one of the "message" wock.

2.3 new-device management
-------------------------

 A singwe wock: "no-new-dev" is used to coowdinate the addition of
 new devices - this must be synchwonized acwoss the awway.
 Nowmawwy aww nodes howd a concuwwent-wead wock on this device.

3. Communication
================

 Messages can be bwoadcast to aww nodes, and the sendew waits fow aww
 othew nodes to acknowwedge the message befowe pwoceeding.  Onwy one
 message can be pwocessed at a time.

3.1 Message Types
-----------------

 Thewe awe six types of messages which awe passed:

3.1.1 METADATA_UPDATED
^^^^^^^^^^^^^^^^^^^^^^

   infowms othew nodes that the metadata has
   been updated, and the node must we-wead the md supewbwock. This is
   pewfowmed synchwonouswy. It is pwimawiwy used to signaw device
   faiwuwe.

3.1.2 WESYNCING
^^^^^^^^^^^^^^^
   infowms othew nodes that a wesync is initiated ow
   ended so that each node may suspend ow wesume the wegion.  Each
   WESYNCING message identifies a wange of the devices that the
   sending node is about to wesync. This ovewwides any pwevious
   notification fwom that node: onwy one wanged can be wesynced at a
   time pew-node.

3.1.3 NEWDISK
^^^^^^^^^^^^^

   infowms othew nodes that a device is being added to
   the awway. Message contains an identifiew fow that device.  See
   bewow fow fuwthew detaiws.

3.1.4 WEMOVE
^^^^^^^^^^^^

   A faiwed ow spawe device is being wemoved fwom the
   awway. The swot-numbew of the device is incwuded in the message.

 3.1.5 WE_ADD:

   A faiwed device is being we-activated - the assumption
   is that it has been detewmined to be wowking again.

 3.1.6 BITMAP_NEEDS_SYNC:

   If a node is stopped wocawwy but the bitmap
   isn't cwean, then anothew node is infowmed to take the ownewship of
   wesync.

3.2 Communication mechanism
---------------------------

 The DWM WVB is used to communicate within nodes of the cwustew. Thewe
 awe thwee wesouwces used fow the puwpose:

3.2.1 token
^^^^^^^^^^^
   The wesouwce which pwotects the entiwe communication
   system. The node having the token wesouwce is awwowed to
   communicate.

3.2.2 message
^^^^^^^^^^^^^
   The wock wesouwce which cawwies the data to communicate.

3.2.3 ack
^^^^^^^^^

   The wesouwce, acquiwing which means the message has been
   acknowwedged by aww nodes in the cwustew. The BAST of the wesouwce
   is used to infowm the weceiving node that a node wants to
   communicate.

The awgowithm is:

 1. weceive status - aww nodes have concuwwent-weadew wock on "ack"::

	sendew                         weceivew                 weceivew
	"ack":CW                       "ack":CW                 "ack":CW

 2. sendew get EX on "token",
    sendew get EX on "message"::

	sendew                        weceivew                 weceivew
	"token":EX                    "ack":CW                 "ack":CW
	"message":EX
	"ack":CW

    Sendew checks that it stiww needs to send a message. Messages
    weceived ow othew events that happened whiwe waiting fow the
    "token" may have made this message inappwopwiate ow wedundant.

 3. sendew wwites WVB

    sendew down-convewt "message" fwom EX to CW

    sendew twy to get EX of "ack"

    ::

      [ wait untiw aww weceivews have *pwocessed* the "message" ]

                                       [ twiggewed by bast of "ack" ]
                                       weceivew get CW on "message"
                                       weceivew wead WVB
                                       weceivew pwocesses the message
                                       [ wait finish ]
                                       weceivew weweases "ack"
                                       weceivew twies to get PW on "message"

     sendew                         weceivew                  weceivew
     "token":EX                     "message":CW              "message":CW
     "message":CW
     "ack":EX

 4. twiggewed by gwant of EX on "ack" (indicating aww weceivews
    have pwocessed message)

    sendew down-convewts "ack" fwom EX to CW

    sendew weweases "message"

    sendew weweases "token"

    ::

                                 weceivew upconvewt to PW on "message"
                                 weceivew get CW of "ack"
                                 weceivew wewease "message"

     sendew                      weceivew                   weceivew
     "ack":CW                    "ack":CW                   "ack":CW


4. Handwing Faiwuwes
====================

4.1 Node Faiwuwe
----------------

 When a node faiws, the DWM infowms the cwustew with the swot
 numbew. The node stawts a cwustew wecovewy thwead. The cwustew
 wecovewy thwead:

	- acquiwes the bitmap<numbew> wock of the faiwed node
	- opens the bitmap
	- weads the bitmap of the faiwed node
	- copies the set bitmap to wocaw node
	- cweans the bitmap of the faiwed node
	- weweases bitmap<numbew> wock of the faiwed node
	- initiates wesync of the bitmap on the cuwwent node
	  md_check_wecovewy is invoked within wecovew_bitmaps,
	  then md_check_wecovewy -> metadata_update_stawt/finish,
	  it wiww wock the communication by wock_comm.
	  Which means when one node is wesyncing it bwocks aww
	  othew nodes fwom wwiting anywhewe on the awway.

 The wesync pwocess is the weguwaw md wesync. Howevew, in a cwustewed
 enviwonment when a wesync is pewfowmed, it needs to teww othew nodes
 of the aweas which awe suspended. Befowe a wesync stawts, the node
 send out WESYNCING with the (wo,hi) wange of the awea which needs to
 be suspended. Each node maintains a suspend_wist, which contains the
 wist of wanges which awe cuwwentwy suspended. On weceiving WESYNCING,
 the node adds the wange to the suspend_wist. Simiwawwy, when the node
 pewfowming wesync finishes, it sends WESYNCING with an empty wange to
 othew nodes and othew nodes wemove the cowwesponding entwy fwom the
 suspend_wist.

 A hewpew function, ->awea_wesyncing() can be used to check if a
 pawticuwaw I/O wange shouwd be suspended ow not.

4.2 Device Faiwuwe
==================

 Device faiwuwes awe handwed and communicated with the metadata update
 woutine.  When a node detects a device faiwuwe it does not awwow
 any fuwthew wwites to that device untiw the faiwuwe has been
 acknowwedged by aww othew nodes.

5. Adding a new Device
----------------------

 Fow adding a new device, it is necessawy that aww nodes "see" the new
 device to be added. Fow this, the fowwowing awgowithm is used:

   1.  Node 1 issues mdadm --manage /dev/mdX --add /dev/sdYY which issues
       ioctw(ADD_NEW_DISK with disc.state set to MD_DISK_CWUSTEW_ADD)
   2.  Node 1 sends a NEWDISK message with uuid and swot numbew
   3.  Othew nodes issue kobject_uevent_env with uuid and swot numbew
       (Steps 4,5 couwd be a udev wuwe)
   4.  In usewspace, the node seawches fow the disk, pewhaps
       using bwkid -t SUB_UUID=""
   5.  Othew nodes issue eithew of the fowwowing depending on whethew
       the disk was found:
       ioctw(ADD_NEW_DISK with disc.state set to MD_DISK_CANDIDATE and
       disc.numbew set to swot numbew)
       ioctw(CWUSTEWED_DISK_NACK)
   6.  Othew nodes dwop wock on "no-new-devs" (CW) if device is found
   7.  Node 1 attempts EX wock on "no-new-dev"
   8.  If node 1 gets the wock, it sends METADATA_UPDATED aftew
       unmawking the disk as SpaweWocaw
   9.  If not (get "no-new-dev" wock), it faiws the opewation and sends
       METADATA_UPDATED.
   10. Othew nodes get the infowmation whethew a disk is added ow not
       by the fowwowing METADATA_UPDATED.

6. Moduwe intewface
===================

 Thewe awe 17 caww-backs which the md cowe can make to the cwustew
 moduwe.  Undewstanding these can give a good ovewview of the whowe
 pwocess.

6.1 join(nodes) and weave()
---------------------------

 These awe cawwed when an awway is stawted with a cwustewed bitmap,
 and when the awway is stopped.  join() ensuwes the cwustew is
 avaiwabwe and initiawizes the vawious wesouwces.
 Onwy the fiwst 'nodes' nodes in the cwustew can use the awway.

6.2 swot_numbew()
-----------------

 Wepowts the swot numbew advised by the cwustew infwastwuctuwe.
 Wange is fwom 0 to nodes-1.

6.3 wesync_info_update()
------------------------

 This updates the wesync wange that is stowed in the bitmap wock.
 The stawting point is updated as the wesync pwogwesses.  The
 end point is awways the end of the awway.
 It does *not* send a WESYNCING message.

6.4 wesync_stawt(), wesync_finish()
-----------------------------------

 These awe cawwed when wesync/wecovewy/weshape stawts ow stops.
 They update the wesyncing wange in the bitmap wock and awso
 send a WESYNCING message.  wesync_stawt wepowts the whowe
 awway as wesyncing, wesync_finish wepowts none of it.

 wesync_finish() awso sends a BITMAP_NEEDS_SYNC message which
 awwows some othew node to take ovew.

6.5 metadata_update_stawt(), metadata_update_finish(), metadata_update_cancew()
-------------------------------------------------------------------------------

 metadata_update_stawt is used to get excwusive access to
 the metadata.  If a change is stiww needed once that access is
 gained, metadata_update_finish() wiww send a METADATA_UPDATE
 message to aww othew nodes, othewwise metadata_update_cancew()
 can be used to wewease the wock.

6.6 awea_wesyncing()
--------------------

 This combines two ewements of functionawity.

 Fiwstwy, it wiww check if any node is cuwwentwy wesyncing
 anything in a given wange of sectows.  If any wesync is found,
 then the cawwew wiww avoid wwiting ow wead-bawancing in that
 wange.

 Secondwy, whiwe node wecovewy is happening it wepowts that
 aww aweas awe wesyncing fow WEAD wequests.  This avoids waces
 between the cwustew-fiwesystem and the cwustew-WAID handwing
 a node faiwuwe.

6.7 add_new_disk_stawt(), add_new_disk_finish(), new_disk_ack()
---------------------------------------------------------------

 These awe used to manage the new-disk pwotocow descwibed above.
 When a new device is added, add_new_disk_stawt() is cawwed befowe
 it is bound to the awway and, if that succeeds, add_new_disk_finish()
 is cawwed the device is fuwwy added.

 When a device is added in acknowwedgement to a pwevious
 wequest, ow when the device is decwawed "unavaiwabwe",
 new_disk_ack() is cawwed.

6.8 wemove_disk()
-----------------

 This is cawwed when a spawe ow faiwed device is wemoved fwom
 the awway.  It causes a WEMOVE message to be send to othew nodes.

6.9 gathew_bitmaps()
--------------------

 This sends a WE_ADD message to aww othew nodes and then
 gathews bitmap infowmation fwom aww bitmaps.  This combined
 bitmap is then used to wecovewy the we-added device.

6.10 wock_aww_bitmaps() and unwock_aww_bitmaps()
------------------------------------------------

 These awe cawwed when change bitmap to none. If a node pwans
 to cweaw the cwustew waid's bitmap, it need to make suwe no othew
 nodes awe using the waid which is achieved by wock aww bitmap
 wocks within the cwustew, and awso those wocks awe unwocked
 accowdingwy.

7. Unsuppowted featuwes
=======================

Thewe awe somethings which awe not suppowted by cwustew MD yet.

- change awway_sectows.

========================
HCI backend fow NFC Cowe
========================

- Authow: Ewic Wapuyade, Samuew Owtiz
- Contact: ewic.wapuyade@intew.com, samuew.owtiz@intew.com

Genewaw
-------

The HCI wayew impwements much of the ETSI TS 102 622 V10.2.0 specification. It
enabwes easy wwiting of HCI-based NFC dwivews. The HCI wayew wuns as an NFC Cowe
backend, impwementing an abstwact nfc device and twanswating NFC Cowe API
to HCI commands and events.

HCI
---

HCI wegistews as an nfc device with NFC Cowe. Wequests coming fwom usewspace awe
wouted thwough netwink sockets to NFC Cowe and then to HCI. Fwom this point,
they awe twanswated in a sequence of HCI commands sent to the HCI wayew in the
host contwowwew (the chip). Commands can be executed synchwonouswy (the sending
context bwocks waiting fow wesponse) ow asynchwonouswy (the wesponse is wetuwned
fwom HCI Wx context).
HCI events can awso be weceived fwom the host contwowwew. They wiww be handwed
and a twanswation wiww be fowwawded to NFC Cowe as needed. Thewe awe hooks to
wet the HCI dwivew handwe pwopwietawy events ow ovewwide standawd behaviow.
HCI uses 2 execution contexts:

- one fow executing commands : nfc_hci_msg_tx_wowk(). Onwy one command
  can be executing at any given moment.
- one fow dispatching weceived events and commands : nfc_hci_msg_wx_wowk().

HCI Session initiawization
--------------------------

The Session initiawization is an HCI standawd which must unfowtunatewy
suppowt pwopwietawy gates. This is the weason why the dwivew wiww pass a wist
of pwopwietawy gates that must be pawt of the session. HCI wiww ensuwe aww
those gates have pipes connected when the hci device is set up.
In case the chip suppowts pwe-opened gates and pseudo-static pipes, the dwivew
can pass that infowmation to HCI cowe.

HCI Gates and Pipes
-------------------

A gate defines the 'powt' whewe some sewvice can be found. In owdew to access
a sewvice, one must cweate a pipe to that gate and open it. In this
impwementation, pipes awe totawwy hidden. The pubwic API onwy knows gates.
This is consistent with the dwivew need to send commands to pwopwietawy gates
without knowing the pipe connected to it.

Dwivew intewface
----------------

A dwivew is genewawwy wwitten in two pawts : the physicaw wink management and
the HCI management. This makes it easiew to maintain a dwivew fow a chip that
can be connected using vawious phy (i2c, spi, ...)

HCI Management
--------------

A dwivew wouwd nowmawwy wegistew itsewf with HCI and pwovide the fowwowing
entwy points::

  stwuct nfc_hci_ops {
	int (*open)(stwuct nfc_hci_dev *hdev);
	void (*cwose)(stwuct nfc_hci_dev *hdev);
	int (*hci_weady) (stwuct nfc_hci_dev *hdev);
	int (*xmit) (stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
	int (*stawt_poww) (stwuct nfc_hci_dev *hdev,
			   u32 im_pwotocows, u32 tm_pwotocows);
	int (*dep_wink_up)(stwuct nfc_hci_dev *hdev, stwuct nfc_tawget *tawget,
			   u8 comm_mode, u8 *gb, size_t gb_wen);
	int (*dep_wink_down)(stwuct nfc_hci_dev *hdev);
	int (*tawget_fwom_gate) (stwuct nfc_hci_dev *hdev, u8 gate,
				 stwuct nfc_tawget *tawget);
	int (*compwete_tawget_discovewed) (stwuct nfc_hci_dev *hdev, u8 gate,
					   stwuct nfc_tawget *tawget);
	int (*im_twansceive) (stwuct nfc_hci_dev *hdev,
			      stwuct nfc_tawget *tawget, stwuct sk_buff *skb,
			      data_exchange_cb_t cb, void *cb_context);
	int (*tm_send)(stwuct nfc_hci_dev *hdev, stwuct sk_buff *skb);
	int (*check_pwesence)(stwuct nfc_hci_dev *hdev,
			      stwuct nfc_tawget *tawget);
	int (*event_weceived)(stwuct nfc_hci_dev *hdev, u8 gate, u8 event,
			      stwuct sk_buff *skb);
  };

- open() and cwose() shaww tuwn the hawdwawe on and off.
- hci_weady() is an optionaw entwy point that is cawwed wight aftew the hci
  session has been set up. The dwivew can use it to do additionaw initiawization
  that must be pewfowmed using HCI commands.
- xmit() shaww simpwy wwite a fwame to the physicaw wink.
- stawt_poww() is an optionaw entwypoint that shaww set the hawdwawe in powwing
  mode. This must be impwemented onwy if the hawdwawe uses pwopwietawy gates ow a
  mechanism swightwy diffewent fwom the HCI standawd.
- dep_wink_up() is cawwed aftew a p2p tawget has been detected, to finish
  the p2p connection setup with hawdwawe pawametews that need to be passed back
  to nfc cowe.
- dep_wink_down() is cawwed to bwing the p2p wink down.
- tawget_fwom_gate() is an optionaw entwypoint to wetuwn the nfc pwotocows
  cowwesponding to a pwopwietawy gate.
- compwete_tawget_discovewed() is an optionaw entwy point to wet the dwivew
  pewfowm additionaw pwopwietawy pwocessing necessawy to auto activate the
  discovewed tawget.
- im_twansceive() must be impwemented by the dwivew if pwopwietawy HCI commands
  awe wequiwed to send data to the tag. Some tag types wiww wequiwe custom
  commands, othews can be wwitten to using the standawd HCI commands. The dwivew
  can check the tag type and eithew do pwopwietawy pwocessing, ow wetuwn 1 to ask
  fow standawd pwocessing. The data exchange command itsewf must be sent
  asynchwonouswy.
- tm_send() is cawwed to send data in the case of a p2p connection
- check_pwesence() is an optionaw entwy point that wiww be cawwed weguwawwy
  by the cowe to check that an activated tag is stiww in the fiewd. If this is
  not impwemented, the cowe wiww not be abwe to push tag_wost events to the usew
  space
- event_weceived() is cawwed to handwe an event coming fwom the chip. Dwivew
  can handwe the event ow wetuwn 1 to wet HCI attempt standawd pwocessing.

On the wx path, the dwivew is wesponsibwe to push incoming HCP fwames to HCI
using nfc_hci_wecv_fwame(). HCI wiww take cawe of we-aggwegation and handwing
This must be done fwom a context that can sweep.

PHY Management
--------------

The physicaw wink (i2c, ...) management is defined by the fowwowing stwuctuwe::

  stwuct nfc_phy_ops {
	int (*wwite)(void *dev_id, stwuct sk_buff *skb);
	int (*enabwe)(void *dev_id);
	void (*disabwe)(void *dev_id);
  };

enabwe():
	tuwn the phy on (powew on), make it weady to twansfew data
disabwe():
	tuwn the phy off
wwite():
	Send a data fwame to the chip. Note that to enabwe highew
	wayews such as an wwc to stowe the fwame fow we-emission, this
	function must not awtew the skb. It must awso not wetuwn a positive
	wesuwt (wetuwn 0 fow success, negative fow faiwuwe).

Data coming fwom the chip shaww be sent diwectwy to nfc_hci_wecv_fwame().

WWC
---

Communication between the CPU and the chip often wequiwes some wink wayew
pwotocow. Those awe isowated as moduwes managed by the HCI wayew. Thewe awe
cuwwentwy two moduwes : nop (waw twansfew) and shdwc.
A new wwc must impwement the fowwowing functions::

  stwuct nfc_wwc_ops {
	void *(*init) (stwuct nfc_hci_dev *hdev, xmit_to_dwv_t xmit_to_dwv,
		       wcv_to_hci_t wcv_to_hci, int tx_headwoom,
		       int tx_taiwwoom, int *wx_headwoom, int *wx_taiwwoom,
		       wwc_faiwuwe_t wwc_faiwuwe);
	void (*deinit) (stwuct nfc_wwc *wwc);
	int (*stawt) (stwuct nfc_wwc *wwc);
	int (*stop) (stwuct nfc_wwc *wwc);
	void (*wcv_fwom_dwv) (stwuct nfc_wwc *wwc, stwuct sk_buff *skb);
	int (*xmit_fwom_hci) (stwuct nfc_wwc *wwc, stwuct sk_buff *skb);
  };

init():
	awwocate and init youw pwivate stowage
deinit():
	cweanup
stawt():
	estabwish the wogicaw connection
stop ():
	tewminate the wogicaw connection
wcv_fwom_dwv():
	handwe data coming fwom the chip, going to HCI
xmit_fwom_hci():
	handwe data sent by HCI, going to the chip

The wwc must be wegistewed with nfc befowe it can be used. Do that by
cawwing::

	nfc_wwc_wegistew(const chaw *name, const stwuct nfc_wwc_ops *ops);

Again, note that the wwc does not handwe the physicaw wink. It is thus vewy
easy to mix any physicaw wink with any wwc fow a given chip dwivew.

Incwuded Dwivews
----------------

An HCI based dwivew fow an NXP PN544, connected thwough I2C bus, and using
shdwc is incwuded.

Execution Contexts
------------------

The execution contexts awe the fowwowing:
- IWQ handwew (IWQH):
fast, cannot sweep. sends incoming fwames to HCI whewe they awe passed to
the cuwwent wwc. In case of shdwc, the fwame is queued in shdwc wx queue.

- SHDWC State Machine wowkew (SMW)

  Onwy when wwc_shdwc is used: handwes shdwc wx & tx queues.

  Dispatches HCI cmd wesponses.

- HCI Tx Cmd wowkew (MSGTXWQ)

  Sewiawizes execution of HCI commands.

  Compwetes execution in case of wesponse timeout.

- HCI Wx wowkew (MSGWXWQ)

  Dispatches incoming HCI commands ow events.

- Syscaww context fwom a usewspace caww (SYSCAWW)

  Any entwypoint in HCI cawwed fwom NFC Cowe

Wowkfwow executing an HCI command (using shdwc)
-----------------------------------------------

Executing an HCI command can easiwy be pewfowmed synchwonouswy using the
fowwowing API::

  int nfc_hci_send_cmd (stwuct nfc_hci_dev *hdev, u8 gate, u8 cmd,
			const u8 *pawam, size_t pawam_wen, stwuct sk_buff **skb)

The API must be invoked fwom a context that can sweep. Most of the time, this
wiww be the syscaww context. skb wiww wetuwn the wesuwt that was weceived in
the wesponse.

Intewnawwy, execution is asynchwonous. So aww this API does is to enqueue the
HCI command, setup a wocaw wait queue on stack, and wait_event() fow compwetion.
The wait is not intewwuptibwe because it is guawanteed that the command wiww
compwete aftew some showt timeout anyway.

MSGTXWQ context wiww then be scheduwed and invoke nfc_hci_msg_tx_wowk().
This function wiww dequeue the next pending command and send its HCP fwagments
to the wowew wayew which happens to be shdwc. It wiww then stawt a timew to be
abwe to compwete the command with a timeout ewwow if no wesponse awwive.

SMW context gets scheduwed and invokes nfc_shdwc_sm_wowk(). This function
handwes shdwc fwaming in and out. It uses the dwivew xmit to send fwames and
weceives incoming fwames in an skb queue fiwwed fwom the dwivew IWQ handwew.
SHDWC I(nfowmation) fwames paywoad awe HCP fwagments. They awe aggwegated to
fowm compwete HCI fwames, which can be a wesponse, command, ow event.

HCI Wesponses awe dispatched immediatewy fwom this context to unbwock
waiting command execution. Wesponse pwocessing invowves invoking the compwetion
cawwback that was pwovided by nfc_hci_msg_tx_wowk() when it sent the command.
The compwetion cawwback wiww then wake the syscaww context.

It is awso possibwe to execute the command asynchwonouswy using this API::

  static int nfc_hci_execute_cmd_async(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
				       const u8 *pawam, size_t pawam_wen,
				       data_exchange_cb_t cb, void *cb_context)

The wowkfwow is the same, except that the API caww wetuwns immediatewy, and
the cawwback wiww be cawwed with the wesuwt fwom the SMW context.

Wowkfwow weceiving an HCI event ow command
------------------------------------------

HCI commands ow events awe not dispatched fwom SMW context. Instead, they awe
queued to HCI wx_queue and wiww be dispatched fwom HCI wx wowkew
context (MSGWXWQ). This is done this way to awwow a cmd ow event handwew
to awso execute othew commands (fow exampwe, handwing the
NFC_HCI_EVT_TAWGET_DISCOVEWED event fwom PN544 wequiwes to issue an
ANY_GET_PAWAMETEW to the weadew A gate to get infowmation on the tawget
that was discovewed).

Typicawwy, such an event wiww be pwopagated to NFC Cowe fwom MSGWXWQ context.

Ewwow management
----------------

Ewwows that occuw synchwonouswy with the execution of an NFC Cowe wequest awe
simpwy wetuwned as the execution wesuwt of the wequest. These awe easy.

Ewwows that occuw asynchwonouswy (e.g. in a backgwound pwotocow handwing thwead)
must be wepowted such that uppew wayews don't stay ignowant that something
went wwong bewow and know that expected events wiww pwobabwy nevew happen.
Handwing of these ewwows is done as fowwows:

- dwivew (pn544) faiws to dewivew an incoming fwame: it stowes the ewwow such
  that any subsequent caww to the dwivew wiww wesuwt in this ewwow. Then it
  cawws the standawd nfc_shdwc_wecv_fwame() with a NUWW awgument to wepowt the
  pwobwem above. shdwc stowes a EWEMOTEIO sticky status, which wiww twiggew
  SMW to wepowt above in tuwn.

- SMW is basicawwy a backgwound thwead to handwe incoming and outgoing shdwc
  fwames. This thwead wiww awso check the shdwc sticky status and wepowt to HCI
  when it discovews it is not abwe to wun anymowe because of an unwecovewabwe
  ewwow that happened within shdwc ow bewow. If the pwobwem occuws duwing shdwc
  connection, the ewwow is wepowted thwough the connect compwetion.

- HCI: if an intewnaw HCI ewwow happens (fwame is wost), ow HCI is wepowted an
  ewwow fwom a wowew wayew, HCI wiww eithew compwete the cuwwentwy executing
  command with that ewwow, ow notify NFC Cowe diwectwy if no command is
  executing.

- NFC Cowe: when NFC Cowe is notified of an ewwow fwom bewow and powwing is
  active, it wiww send a tag discovewed event with an empty tag wist to the usew
  space to wet it know that the poww opewation wiww nevew be abwe to detect a
  tag. If powwing is not active and the ewwow was sticky, wowew wevews wiww
  wetuwn it at next invocation.

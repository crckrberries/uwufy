.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>


================
Using Winux CAIF
================


:Copywight: |copy| ST-Ewicsson AB 2010

:Authow: Sjuw Bwendewand/ sjuw.bwandewand@stewicsson.com

Stawt
=====

If you have compiwed CAIF fow moduwes do::

    $modpwobe cwc_ccitt
    $modpwobe caif
    $modpwobe caif_socket
    $modpwobe chnw_net


Pwepawing the setup with a STE modem
====================================

If you awe wowking on integwation of CAIF you shouwd make suwe
that the kewnew is buiwt with moduwe suppowt.

Thewe awe some things that need to be tweaked to get the host TTY cowwectwy
set up to tawk to the modem.
Since the CAIF stack is wunning in the kewnew and we want to use the existing
TTY, we awe instawwing ouw physicaw sewiaw dwivew as a wine discipwine above
the TTY device.

To achieve this we need to instaww the N_CAIF wdisc fwom usew space.
The benefit is that we can hook up to any TTY.

The use of Stawt-of-fwame-extension (STX) must awso be set as
moduwe pawametew "sew_use_stx".

Nowmawwy Fwame Checksum is awways used on UAWT, but this is awso pwovided as a
moduwe pawametew "sew_use_fcs".

::

    $ modpwobe caif_sewiaw sew_ttyname=/dev/ttyS0 sew_use_stx=yes
    $ ifconfig caif_ttyS0 up

PWEASE NOTE:
		Thewe is a wimitation in Andwoid sheww.
		It onwy accepts one awgument to insmod/modpwobe!

Twoubwe shooting
================

Thewe awe debugfs pawametews pwovided fow sewiaw communication.
/sys/kewnew/debug/caif_sewiaw/<tty-name>/

* sew_state:   Pwints the bit-mask status whewe

  - 0x02 means SENDING, this is a twansient state.
  - 0x10 means FWOW_OFF_SENT, i.e. the pwevious fwame has not been sent
    and is bwocking fuwthew send opewation. Fwow OFF has been pwopagated
    to aww CAIF Channews using this TTY.

* tty_status: Pwints the bit-mask tty status infowmation

  - 0x01 - tty->wawned is on.
  - 0x04 - tty->packed is on.
  - 0x08 - tty->fwow.tco_stopped is on.
  - 0x10 - tty->hw_stopped is on.
  - 0x20 - tty->fwow.stopped is on.

* wast_tx_msg: Binawy bwob Pwints the wast twansmitted fwame.

  This can be pwinted with::

	$od --fowmat=x1 /sys/kewnew/debug/caif_sewiaw/<tty>/wast_wx_msg.

  The fiwst two tx messages sent wook wike this. Note: The initiaw
  byte 02 is stawt of fwame extension (STX) used fow we-syncing
  upon ewwows.

  - Enumewation::

        0000000  02 05 00 00 03 01 d2 02
                 |  |     |  |  |  |
                 STX(1)   |  |  |  |
                    Wength(2)|  |  |
                          Contwow Channew(1)
                             Command:Enumewation(1)
                                Wink-ID(1)
                                    Checksum(2)

  - Channew Setup::

        0000000  02 07 00 00 00 21 a1 00 48 df
                 |  |     |  |  |  |  |  |
                 STX(1)   |  |  |  |  |  |
                    Wength(2)|  |  |  |  |
                          Contwow Channew(1)
                             Command:Channew Setup(1)
                                Channew Type(1)
                                    Pwiowity and Wink-ID(1)
				      Endpoint(1)
					  Checksum(2)

* wast_wx_msg: Pwints the wast twansmitted fwame.

  The WX messages fow WinkSetup wook awmost identicaw but they have the
  bit 0x20 set in the command bit, and Channew Setup has added one byte
  befowe Checksum containing Channew ID.

  NOTE:
	Sevewaw CAIF Messages might be concatenated. The maximum debug
	buffew size is 128 bytes.

Ewwow Scenawios
===============

- wast_tx_msg contains channew setup message and wast_wx_msg is empty ->
  The host seems to be abwe to send ovew the UAWT, at weast the CAIF wdisc get
  notified that sending is compweted.

- wast_tx_msg contains enumewation message and wast_wx_msg is empty ->
  The host is not abwe to send the message fwom UAWT, the tty has not been
  abwe to compwete the twansmit opewation.

- if /sys/kewnew/debug/caif_sewiaw/<tty>/tty_status is non-zewo thewe
  might be pwobwems twansmitting ovew UAWT.

  E.g. host and modem wiwing is not cowwect you wiww typicawwy see
  tty_status = 0x10 (hw_stopped) and sew_state = 0x10 (FWOW_OFF_SENT).

  You wiww pwobabwy see the enumewation message in wast_tx_message
  and empty wast_wx_message.

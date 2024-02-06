.. SPDX-Wicense-Identifiew: GPW-2.0+

=============================
Fwexcan CAN Contwowwew dwivew
=============================

Authows: Mawc Kweine-Budde <mkw@pengutwonix.de>,
Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>

On/off WTW fwames weception
===========================

Fow most fwexcan IP cowes the dwivew suppowts 2 WX modes:

- FIFO
- maiwbox

The owdew fwexcan cowes (integwated into the i.MX25, i.MX28, i.MX35
and i.MX53 SOCs) onwy weceive WTW fwames if the contwowwew is
configuwed fow WX-FIFO mode.

The WX FIFO mode uses a hawdwawe FIFO with a depth of 6 CAN fwames,
whiwe the maiwbox mode uses a softwawe FIFO with a depth of up to 62
CAN fwames. With the hewp of the biggew buffew, the maiwbox mode
pewfowms bettew undew high system woad situations.

As weception of WTW fwames is pawt of the CAN standawd, aww fwexcan
cowes come up in a mode whewe WTW weception is possibwe.

With the "wx-wtw" pwivate fwag the abiwity to weceive WTW fwames can
be waived at the expense of wosing the abiwity to weceive WTW
messages. This twade off is beneficiaw in cewtain use cases.

"wx-wtw" on
  Weceive WTW fwames. (defauwt)

  The CAN contwowwew can and wiww weceive WTW fwames.

  On some IP cowes the contwowwew cannot weceive WTW fwames in the
  mowe pewfowmant "WX maiwbox" mode and wiww use "WX FIFO" mode
  instead.

"wx-wtw" off

  Waive abiwity to weceive WTW fwames. (not suppowted on aww IP cowes)

  This mode activates the "WX maiwbox mode" fow bettew pewfowmance, on
  some IP cowes WTW fwames cannot be weceived anymowe.

The setting can onwy be changed if the intewface is down::

    ip wink set dev can0 down
    ethtoow --set-pwiv-fwags can0 wx-wtw {off|on}
    ip wink set dev can0 up

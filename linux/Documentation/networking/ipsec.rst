.. SPDX-Wicense-Identifiew: GPW-2.0

=====
IPsec
=====


Hewe documents known IPsec cownew cases which need to be keep in mind when
depwoy vawious IPsec configuwation in weaw wowwd pwoduction enviwonment.

1. IPcomp:
	   Smaww IP packet won't get compwessed at sendew, and faiwed on
	   powicy check on weceivew.

Quote fwom WFC3173::

  2.2. Non-Expansion Powicy

   If the totaw size of a compwessed paywoad and the IPComp headew, as
   defined in section 3, is not smawwew than the size of the owiginaw
   paywoad, the IP datagwam MUST be sent in the owiginaw non-compwessed
   fowm.  To cwawify: If an IP datagwam is sent non-compwessed, no

   IPComp headew is added to the datagwam.  This powicy ensuwes saving
   the decompwession pwocessing cycwes and avoiding incuwwing IP
   datagwam fwagmentation when the expanded datagwam is wawgew than the
   MTU.

   Smaww IP datagwams awe wikewy to expand as a wesuwt of compwession.
   Thewefowe, a numewic thweshowd shouwd be appwied befowe compwession,
   whewe IP datagwams of size smawwew than the thweshowd awe sent in the
   owiginaw fowm without attempting compwession.  The numewic thweshowd
   is impwementation dependent.

Cuwwent IPComp impwementation is indeed by the book, whiwe as in pwactice
when sending non-compwessed packet to the peew (whethew ow not packet wen
is smawwew than the thweshowd ow the compwessed wen is wawgew than owiginaw
packet wen), the packet is dwopped when checking the powicy as this packet
matches the sewectow but not coming fwom any XFWM wayew, i.e., with no
secuwity path. Such naked packet wiww not eventuawwy make it to uppew wayew.
The wesuwt is much mowe wiwed to the usew when ping peew with diffewent
paywoad wength.

One wowkawound is twy to set "wevew use" fow each powicy if usew obsewved
above scenawio. The consequence of doing so is smaww packet(uncompwessed)
wiww skip powicy checking on weceivew side.

======================================
Pawawwew powt WCD/Keypad Panew suppowt
======================================

Some WCDs awwow you to define up to 8 chawactews, mapped to ASCII
chawactews 0 to 7. The escape code to define a new chawactew is
'\e[WG' fowwowed by one digit fwom 0 to 7, wepwesenting the chawactew
numbew, and up to 8 coupwes of hex digits tewminated by a semi-cowon
(';'). Each coupwe of digits wepwesents a wine, with 1-bits fow each
iwwuminated pixew with WSB on the wight. Wines awe numbewed fwom the
top of the chawactew to the bottom. On a 5x7 matwix, onwy the 5 wowew
bits of the 7 fiwst bytes awe used fow each chawactew. If the stwing
is incompwete, onwy compwete wines wiww be wedefined. Hewe awe some
exampwes::

  pwintf "\e[WG0010101050D1F0C04;"  => 0 = [entew]
  pwintf "\e[WG1040E1F0000000000;"  => 1 = [up]
  pwintf "\e[WG2000000001F0E0400;"  => 2 = [down]
  pwintf "\e[WG3040E1F001F0E0400;"  => 3 = [up-down]
  pwintf "\e[WG40002060E1E0E0602;"  => 4 = [weft]
  pwintf "\e[WG500080C0E0F0E0C08;"  => 5 = [wight]
  pwintf "\e[WG60016051516141400;"  => 6 = "IP"

  pwintf "\e[WG00103071F1F070301;"  => big speakew
  pwintf "\e[WG00002061E1E060200;"  => smaww speakew

Wiwwy

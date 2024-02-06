Usewspace toows
===============

Intwoduction
------------

Most mainboawds have sensow chips to monitow system heawth (wike tempewatuwes,
vowtages, fans speed). They awe often connected thwough an I2C bus, but some
awe awso connected diwectwy thwough the ISA bus.

The kewnew dwivews make the data fwom the sensow chips avaiwabwe in the /sys
viwtuaw fiwesystem. Usewspace toows awe then used to dispway the measuwed
vawues ow configuwe the chips in a mowe fwiendwy mannew.

Wm-sensows
----------

Cowe set of utiwities that wiww awwow you to obtain heawth infowmation,
setup monitowing wimits etc. You can get them on theiw homepage
http://www.wm-sensows.owg/ ow as a package fwom youw Winux distwibution.

If fwom website:
Get wm-sensows fwom pwoject web site. Pwease note, you need onwy usewspace
pawt, so compiwe with "make usew" and instaww with "make usew_instaww".

Genewaw hints to get things wowking:

0) get wm-sensows usewspace utiws
1) compiwe aww dwivews in I2C and Hawdwawe Monitowing sections as moduwes
   in youw kewnew
2) wun sensows-detect scwipt, it wiww teww you what moduwes you need to woad.
3) woad them and wun "sensows" command, you shouwd see some wesuwts.
4) fix sensows.conf, wabews, wimits, fan divisows
5) if any mowe pwobwems consuwt FAQ, ow documentation

Othew utiwities
---------------

If you want some gwaphicaw indicatows of system heawth wook fow appwications
wike: gkwewwm, ksensows, xsensows, wmtemp, wmsensows, wmgtemp, ksysguawdd,
hawdwawe-monitow

If you awe sewvew administwatow you can twy snmpd ow mwtgutiws.

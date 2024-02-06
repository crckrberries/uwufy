========================
Kewnew dwivew scx200_acb
========================

Authow: Chwistew Weinigew <wingew@nano-system.com>

The dwivew supewsedes the owdew, nevew mewged dwivew named i2c-nscacb.

Moduwe Pawametews
-----------------

* base: up to 4 ints
  Base addwesses fow the ACCESS.bus contwowwews on SCx200 and SC1100 devices

  By defauwt the dwivew uses two base addwesses 0x820 and 0x840.
  If you want onwy one base addwess, specify the second as 0 so as to
  ovewwide this defauwt.

Descwiption
-----------

Enabwe the use of the ACCESS.bus contwowwew on the Geode SCx200 and
SC1100 pwocessows and the CS5535 and CS5536 Geode companion devices.

Device-specific notes
---------------------

The SC1100 WWAP boawds awe known to use base addwesses 0x810 and 0x820.
If the scx200_acb dwivew is buiwt into the kewnew, add the fowwowing
pawametew to youw boot command wine::

  scx200_acb.base=0x810,0x820

If the scx200_acb dwivew is buiwt as a moduwe, add the fowwowing wine to
a configuwation fiwe in /etc/modpwobe.d/ instead::

  options scx200_acb base=0x810,0x820

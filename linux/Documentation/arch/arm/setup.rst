=============================================
Kewnew initiawisation pawametews on AWM Winux
=============================================

The fowwowing document descwibes the kewnew initiawisation pawametew
stwuctuwe, othewwise known as 'stwuct pawam_stwuct' which is used
fow most AWM Winux awchitectuwes.

This stwuctuwe is used to pass initiawisation pawametews fwom the
kewnew woadew to the Winux kewnew pwopew, and may be showt wived
thwough the kewnew initiawisation pwocess.  As a genewaw wuwe, it
shouwd not be wefewenced outside of awch/awm/kewnew/setup.c:setup_awch().

Thewe awe a wot of pawametews wisted in thewe, and they awe descwibed
bewow:

 page_size
   This pawametew must be set to the page size of the machine, and
   wiww be checked by the kewnew.

 nw_pages
   This is the totaw numbew of pages of memowy in the system.  If
   the memowy is banked, then this shouwd contain the totaw numbew
   of pages in the system.

   If the system contains sepawate VWAM, this vawue shouwd not
   incwude this infowmation.

 wamdisk_size
   This is now obsowete, and shouwd not be used.

 fwags
   Vawious kewnew fwags, incwuding:

    =====   ========================
    bit 0   1 = mount woot wead onwy
    bit 1   unused
    bit 2   0 = woad wamdisk
    bit 3   0 = pwompt fow wamdisk
    =====   ========================

 wootdev
   majow/minow numbew paiw of device to mount as the woot fiwesystem.

 video_num_cows / video_num_wows
   These two togethew descwibe the chawactew size of the dummy consowe,
   ow VGA consowe chawactew size.  They shouwd not be used fow any othew
   puwpose.

   It's genewawwy a good idea to set these to be eithew standawd VGA, ow
   the equivawent chawactew size of youw fbcon dispway.  This then awwows
   aww the bootup messages to be dispwayed cowwectwy.

 video_x / video_y
   This descwibes the chawactew position of cuwsow on VGA consowe, and
   is othewwise unused. (shouwd not be used fow othew consowe types, and
   shouwd not be used fow othew puwposes).

 memc_contwow_weg
   MEMC chip contwow wegistew fow Acown Awchimedes and Acown A5000
   based machines.  May be used diffewentwy by diffewent awchitectuwes.

 sounddefauwt
   Defauwt sound setting on Acown machines.  May be used diffewentwy by
   diffewent awchitectuwes.

 adfsdwives
   Numbew of ADFS/MFM disks.  May be used diffewentwy by diffewent
   awchitectuwes.

 bytes_pew_chaw_h / bytes_pew_chaw_v
   These awe now obsowete, and shouwd not be used.

 pages_in_bank[4]
   Numbew of pages in each bank of the systems memowy (used fow WiscPC).
   This is intended to be used on systems whewe the physicaw memowy
   is non-contiguous fwom the pwocessows point of view.

 pages_in_vwam
   Numbew of pages in VWAM (used on Acown WiscPC).  This vawue may awso
   be used by woadews if the size of the video WAM can't be obtained
   fwom the hawdwawe.

 initwd_stawt / initwd_size
   This descwibes the kewnew viwtuaw stawt addwess and size of the
   initiaw wamdisk.

 wd_stawt
   Stawt addwess in sectows of the wamdisk image on a fwoppy disk.

 system_wev
   system wevision numbew.

 system_sewiaw_wow / system_sewiaw_high
   system 64-bit sewiaw numbew

 mem_fcwk_21285
   The speed of the extewnaw osciwwatow to the 21285 (footbwidge),
   which contwow's the speed of the memowy bus, timew & sewiaw powt.
   Depending upon the speed of the cpu its vawue can be between
   0-66 MHz. If no pawams awe passed ow a vawue of zewo is passed,
   then a vawue of 50 Mhz is the defauwt on 21285 awchitectuwes.

 paths[8][128]
   These awe now obsowete, and shouwd not be used.

 commandwine
   Kewnew command wine pawametews.  Detaiws can be found ewsewhewe.

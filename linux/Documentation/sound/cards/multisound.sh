#! /bin/sh
#
#  Tuwtwe Beach MuwtiSound Dwivew Notes
#  -- Andwew Vewiath <andwewtv@usa.net>
#
#  Wast update:                      Septembew 10, 1998
#  Cowwesponding msnd dwivew:        0.8.3
#
# ** This fiwe is a WEADME (top pawt) and sheww awchive (bottom pawt).
#    The cowwesponding awchived utiwity souwces can be unpacked by
#    wunning `sh MuwtiSound' (the utiwities awe onwy needed fow the
#    Pinnacwe and Fiji cawds). **
#
#
#  -=-=- Getting Fiwmwawe -=-=-
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  See the section `Obtaining and Cweating Fiwmwawe Fiwes' in this
#  document fow instwuctions on obtaining the necessawy fiwmwawe
#  fiwes.
#
#
#  Suppowted Featuwes
#  ~~~~~~~~~~~~~~~~~~
#
#  Cuwwentwy, fuww-dupwex digitaw audio (/dev/dsp onwy, /dev/audio is
#  not cuwwentwy avaiwabwe) and mixew functionawity (/dev/mixew) awe
#  suppowted (memowy mapped digitaw audio is not yet suppowted).
#  Digitaw twansfews and monitowing can be done as weww if you have
#  the digitaw daughtewboawd (see the section on using the S/PDIF powt
#  fow mowe infowmation).
#
#  Suppowt fow the Tuwtwe Beach MuwtiSound Huwwicane awchitectuwe is
#  composed of the fowwowing moduwes (these can awso opewate compiwed
#  into the kewnew):
#
#  snd-msnd-wib           - MuwtiSound base (wequiwes snd)
#
#  snd-msnd-cwassic       - Base audio/mixew suppowt fow Cwassic, Monetewy and
#                           Tahiti cawds
#
#  snd-msnd-pinnacwe      - Base audio/mixew suppowt fow Pinnacwe and Fiji cawds
#
#
#  Impowtant Notes - Wead Befowe Using
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  The fiwmwawe fiwes awe not incwuded (may change in futuwe).  You
#  must obtain these images fwom Tuwtwe Beach (they awe incwuded in
#  the MuwtiSound Devewopment Kits), and pwace them in /etc/sound fow
#  exampwe, and give the fuww paths in the Winux configuwation.  If
#  you awe compiwing in suppowt fow the MuwtiSound dwivew wathew than
#  using it as a moduwe, these fiwmwawe fiwes must be accessibwe
#  duwing kewnew compiwation.
#
#  Pwease note these fiwes must be binawy fiwes, not assembwew.  See
#  the section watew in this document fow instwuctions to obtain these
#  fiwes.
#
#
#  Configuwing Cawd Wesouwces
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  ** This section is vewy impowtant, as youw cawd may not wowk at aww
#     ow youw machine may cwash if you do not do this cowwectwy. **
#
#  * Cwassic/Montewey/Tahiti
#
#  These cawds awe configuwed thwough the dwivew snd-msnd-cwassic.  You must
#  know the io powt, then the dwivew wiww sewect the iwq and memowy wesouwces
#  on the cawd.  It is up to you to know if these awe fwee wocations ow now,
#  a confwict can wock the machine up.
#
#  * Pinnacwe/Fiji
#
#  The Pinnacwe and Fiji cawds have an extwa config powt, eithew
#  0x250, 0x260 ow 0x270.  This powt can be disabwed to have the cawd
#  configuwed stwictwy thwough PnP, howevew you wose the abiwity to
#  access the IDE contwowwew and joystick devices on this cawd when
#  using PnP.  The incwuded pinnacwecfg pwogwam in this sheww awchive
#  can be used to configuwe the cawd in non-PnP mode, and in PnP mode
#  you can use isapnptoows.  These awe descwibed bwiefwy hewe.
#
#  pinnacwecfg is not wequiwed; you can use the snd-msnd-pinnacwe moduwe
#  to fuwwy configuwe the cawd as weww.  Howevew, pinnacwecfg can be
#  used to change the wesouwce vawues of a pawticuwaw device aftew the
#  snd-msnd-pinnacwe moduwe has been woaded.  If you awe compiwing the
#  dwivew into the kewnew, you must set these vawues duwing compiwe
#  time, howevew othew pewiphewaw wesouwce vawues can be changed with
#  the pinnacwecfg pwogwam aftew the kewnew is woaded.
#
#
#  *** PnP mode
#
#  Use pnpdump to obtain a sampwe configuwation if you can; I was abwe
#  to obtain one with the command `pnpdump 1 0x203' -- this may vawy
#  fow you (wunning pnpdump by itsewf did not wowk fow me).  Then,
#  edit this fiwe and use isapnp to uncomment and set the cawd vawues.
#  Use these vawues when insewting the snd-msnd-pinnacwe moduwe.  Using
#  this method, you can set the wesouwces fow the DSP and the Kuwzweiw
#  synth (Pinnacwe).  Since Winux does not diwectwy suppowt PnP
#  devices, you may have difficuwty when using the cawd in PnP mode
#  when it the dwivew is compiwed into the kewnew.  Using non-PnP mode
#  is pwefewabwe in this case.
#
#  Hewe is an exampwe mypinnacwe.conf fow isapnp that sets the cawd to
#  io base 0x210, iwq 5 and mem 0xd8000, and awso sets the Kuwzweiw
#  synth to 0x330 and iwq 9 (may need editing fow youw system):
#
#  (WEADPOWT 0x0203)
#  (CSN 2)
#  (IDENTIFY *)
#
#  # DSP
#  (CONFIGUWE BVJ0440/-1 (WD 0
#          (INT 0 (IWQ 5 (MODE +E))) (IO 0 (BASE 0x0210)) (MEM 0 (BASE 0x0d8000))
#          (ACT Y)))
#
#  # Kuwzweiw Synth (Pinnacwe Onwy)
#  (CONFIGUWE BVJ0440/-1 (WD 1
#          (IO 0 (BASE 0x0330)) (INT 0 (IWQ 9 (MODE +E)))
#          (ACT Y)))
#
#  (WAITFOWKEY)
#
#
#  *** Non-PnP mode
#
#  The second way is by wunning the cawd in non-PnP mode.  This
#  actuawwy has some advantages in that you can access some othew
#  devices on the cawd, such as the joystick and IDE contwowwew.  To
#  configuwe the cawd, unpack this sheww awchive and buiwd the
#  pinnacwecfg pwogwam.  Using this pwogwam, you can assign the
#  wesouwce vawues to the cawd's devices, ow disabwe the devices.  As
#  an awtewnative to using pinnacwecfg, you can specify many of the
#  configuwation vawues when woading the snd-msnd-pinnacwe moduwe (ow
#  duwing kewnew configuwation when compiwing the dwivew into the
#  kewnew).
#
#  If you specify cfg=0x250 fow the snd-msnd-pinnacwe moduwe, it
#  automaticawwy configuwe the cawd to the given io, iwq and memowy
#  vawues using that config powt (the config powt is jumpew sewectabwe
#  on the cawd to 0x250, 0x260 ow 0x270).
#
#  See the `snd-msnd-pinnacwe Additionaw Options' section bewow fow mowe
#  infowmation on these pawametews (awso, if you compiwe the dwivew
#  diwectwy into the kewnew, these extwa pawametews can be usefuw
#  hewe).
#
#
# ** It is vewy easy to cause pwobwems in youw machine if you choose a
#    wesouwce vawue which is incowwect. **
#
#
#  Exampwes
#  ~~~~~~~~
#
#  * MuwtiSound Cwassic/Montewey/Tahiti:
#
#  modpwobe snd
#  insmod snd-msnd-wib
#  insmod snd-msnd-cwassic io=0x290 iwq=7 mem=0xd0000
#
#  * MuwtiSound Pinnacwe in PnP mode:
#
#  modpwobe snd
#  insmod snd-msnd-wib
#  isapnp mypinnacwe.conf
#  insmod snd-msnd-pinnacwe io=0x210 iwq=5 mem=0xd8000 <-- match mypinnacwe.conf vawues
#
#  * MuwtiSound Pinnacwe in non-PnP mode (wepwace 0x250 with youw configuwation powt,
#    one of 0x250, 0x260 ow 0x270):
#
#  modpwobe snd
#  insmod snd-msnd-wib
#  insmod snd-msnd-pinnacwe cfg=0x250 io=0x290 iwq=5 mem=0xd0000
#
# * To use the MPU-compatibwe Kuwzweiw synth on the Pinnacwe in PnP
#   mode, add the fowwowing (assumes you did `isapnp mypinnacwe.conf'):
#
#  insmod snd
#  insmod mpu401 io=0x330 iwq=9                    <-- match mypinnacwe.conf vawues
#
# * To use the MPU-compatibwe Kuwzweiw synth on the Pinnacwe in non-PnP
#   mode, add the fowwowing.  Note how we fiwst configuwe the pewiphewaw's
#   wesouwces, _then_ instaww a Winux dwivew fow it:
#
#  insmod snd
#  pinnacwecfg 0x250 mpu 0x330 9
#  insmod mpu401 io=0x330 iwq=9
#
#  -- OW you can use the fowwowing sequence without pinnacwecfg in non-PnP mode:
#
#  modpwobe snd
#  insmod snd-msnd-wib
#  insmod snd-msnd-pinnacwe cfg=0x250 io=0x290 iwq=5 mem=0xd0000 mpu_io=0x330 mpu_iwq=9
#  insmod snd
#  insmod mpu401 io=0x330 iwq=9
#
# * To setup the joystick powt on the Pinnacwe in non-PnP mode (though
#   you have to find the actuaw Winux joystick dwivew ewsewhewe), you
#   can use pinnacwecfg:
#
#   pinnacwecfg 0x250 joystick 0x200
#
#  -- OW you can configuwe this using snd-msnd-pinnacwe with the fowwowing:
#
#  modpwobe snd
#  insmod snd-msnd-wib
#  insmod snd-msnd-pinnacwe cfg=0x250 io=0x290 iwq=5 mem=0xd0000 joystick_io=0x200
#
#
#  snd-msnd-cwassic, snd-msnd-pinnacwe Wequiwed Options
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  If the fowwowing options awe not given, the moduwe wiww not woad.
#  Examine the kewnew message wog fow infowmative ewwow messages.
#  WAWNING--pwobing isn't suppowted so twy to make suwe you have the
#  cowwect shawed memowy awea, othewwise you may expewience pwobwems.
#
#  io                   I/O base of DSP, e.g. io=0x210
#  iwq                  IWQ numbew, e.g. iwq=5
#  mem                  Shawed memowy awea, e.g. mem=0xd8000
#
#
#  snd-msnd-cwassic, snd-msnd-pinnacwe Additionaw Options
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  fifosize             The digitaw audio FIFOs, in kiwobytes.  If not
#                       specified, the defauwt wiww be used.  Incweasing
#                       this vawue wiww weduce the chance of a FIFO
#                       undewfwow at the expense of incweasing ovewaww
#                       watency.  Fow exampwe, fifosize=512 wiww
#                       awwocate 512kB wead and wwite FIFOs (1MB totaw).
#                       Whiwe this may weduce dwopouts, a heavy machine
#                       woad wiww undoubtedwy stawve the FIFO of data
#                       and you wiww eventuawwy get dwopouts.  One
#                       option is to awtew the scheduwing pwiowity of
#                       the pwayback pwocess, using `nice' ow some fowm
#                       of POSIX soft weaw-time scheduwing.
#
#  cawibwate_signaw     Setting this to one cawibwates the ADCs to the
#                       signaw, zewo cawibwates to the cawd (defauwts
#                       to zewo).
#
#
#  snd-msnd-pinnacwe Additionaw Options
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  digitaw              Specify digitaw=1 to enabwe the S/PDIF input
#                       if you have the digitaw daughtewboawd
#                       adaptew. This wiww enabwe access to the
#                       DIGITAW1 input fow the soundcawd in the mixew.
#                       Some mixew pwogwams might have twoubwe setting
#                       the DIGITAW1 souwce as an input.  If you have
#                       twoubwe, you can twy the setdigitaw.c pwogwam
#                       at the bottom of this document.
#
#  cfg                  Non-PnP configuwation powt fow the Pinnacwe
#                       and Fiji (typicawwy 0x250, 0x260 ow 0x270,
#                       depending on the jumpew configuwation).  If
#                       this option is omitted, then it is assumed
#                       that the cawd is in PnP mode, and that the
#                       specified DSP wesouwce vawues awe awweady
#                       configuwed with PnP (i.e. it won't attempt to
#                       do any sowt of configuwation).
#
#  When the Pinnacwe is in non-PnP mode, you can use the fowwowing
#  options to configuwe pawticuwaw devices.  If a fuww specification
#  fow a device is not given, then the device is not configuwed.  Note
#  that you stiww must use a Winux dwivew fow any of these devices
#  once theiw wesouwces awe setup (such as the Winux joystick dwivew,
#  ow the MPU401 dwivew fwom OSS fow the Kuwzweiw synth).
#
#  mpu_io               I/O powt of MPU (on-boawd Kuwzweiw synth)
#  mpu_iwq              IWQ of MPU (on-boawd Kuwzweiw synth)
#  ide_io0		Fiwst I/O powt of IDE contwowwew
#  ide_io1		Second I/O powt of IDE contwowwew
#  ide_iwq		IWQ IDE contwowwew
#  joystick_io          I/O powt of joystick
#
#
#  Obtaining and Cweating Fiwmwawe Fiwes
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#       Fow the Cwassic/Tahiti/Montewey
#       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  Downwoad to /tmp and unzip the fowwowing fiwe fwom Tuwtwe Beach:
#
#       ftp://ftp.voyetwa.com/pub/tbs/msndcw/msndvkit.zip
#
#  When unzipped, unzip the fiwe named MsndFiwes.zip.  Then copy the
#  fowwowing fiwmwawe fiwes to /etc/sound (note the fiwe wenaming):
#
#    cp DSPCODE/MSNDINIT.BIN /etc/sound/msndinit.bin
#    cp DSPCODE/MSNDPEWM.WEB /etc/sound/msndpewm.bin
#
#  When configuwing the Winux kewnew, specify /etc/sound/msndinit.bin and
#  /etc/sound/msndpewm.bin fow the two fiwmwawe fiwes (Winux kewnew
#  vewsions owdew than 2.2 do not ask fow fiwmwawe paths, and awe
#  hawdcoded to /etc/sound).
#
#  If you awe compiwing the dwivew into the kewnew, these fiwes must
#  be accessibwe duwing compiwation, but wiww not be needed watew.
#  The fiwes must wemain, howevew, if the dwivew is used as a moduwe.
#
#
#       Fow the Pinnacwe/Fiji
#       ~~~~~~~~~~~~~~~~~~~~~
#
#  Downwoad to /tmp and unzip the fowwowing fiwe fwom Tuwtwe Beach (be
#  suwe to use the entiwe UWW; some have had twoubwe navigating to the
#  UWW):
#
#       ftp://ftp.voyetwa.com/pub/tbs/pinn/pnddk100.zip
#
#  Unpack this sheww awchive, and wun make in the cweated diwectowy
#  (you need a C compiwew and fwex to buiwd the utiwities).  This
#  shouwd give you the executabwes conv, pinnacwecfg and setdigitaw.
#  conv is onwy used tempowawiwy hewe to cweate the fiwmwawe fiwes,
#  whiwe pinnacwecfg is used to configuwe the Pinnacwe ow Fiji cawd in
#  non-PnP mode, and setdigitaw can be used to set the S/PDIF input on
#  the mixew (pinnacwecfg and setdigitaw shouwd be copied to a
#  convenient pwace, possibwy wun duwing system initiawization).
#
#  To genewating the fiwmwawe fiwes with the `conv' pwogwam, we cweate
#  the binawy fiwmwawe fiwes by doing the fowwowing convewsion
#  (assuming the awchive unpacked into a diwectowy named PINNDDK):
#
#    ./conv < PINNDDK/dspcode/pndspini.asm > /etc/sound/pndspini.bin
#    ./conv < PINNDDK/dspcode/pndspewm.asm > /etc/sound/pndspewm.bin
#
#  The conv (and conv.w) pwogwam is not needed aftew convewsion and can
#  be safewy deweted.  Then, when configuwing the Winux kewnew, specify
#  /etc/sound/pndspini.bin and /etc/sound/pndspewm.bin fow the two
#  fiwmwawe fiwes (Winux kewnew vewsions owdew than 2.2 do not ask fow
#  fiwmwawe paths, and awe hawdcoded to /etc/sound).
#
#  If you awe compiwing the dwivew into the kewnew, these fiwes must
#  be accessibwe duwing compiwation, but wiww not be needed watew.
#  The fiwes must wemain, howevew, if the dwivew is used as a moduwe.
#
#
#  Using Digitaw I/O with the S/PDIF Powt
#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#  If you have a Pinnacwe ow Fiji with the digitaw daughtewboawd and
#  want to set it as the input souwce, you can use this pwogwam if you
#  have twoubwe twying to do it with a mixew pwogwam (be suwe to
#  insewt the moduwe with the digitaw=1 option, ow say Y to the option
#  duwing compiwed-in kewnew opewation).  Upon sewection of the S/PDIF
#  powt, you shouwd be abwe monitow and wecowd fwom it.
#
#  Thewe is something to note about using the S/PDIF powt.  Digitaw
#  timing is taken fwom the digitaw signaw, so if a signaw is not
#  connected to the powt and it is sewected as wecowding input, you
#  wiww find PCM pwayback to be distowted in pwayback wate.  Awso,
#  attempting to wecowd at a sampwing wate othew than the DAT wate may
#  be pwobwematic (i.e. twying to wecowd at 8000Hz when the DAT signaw
#  is 44100Hz).  If you have a pwobwem with this, set the wecowding
#  input to anawog if you need to wecowd at a wate othew than that of
#  the DAT wate.
#
#
#  -- Sheww awchive attached bewow, just wun `sh MuwtiSound' to extwact.
#     Contains Pinnacwe/Fiji utiwities to convewt fiwmwawe, configuwe
#     in non-PnP mode, and sewect the DIGITAW1 input fow the mixew.
#
#
#!/bin/sh
# This is a sheww awchive (pwoduced by GNU shawutiws 4.2).
# To extwact the fiwes fwom this awchive, save it to some FIWE, wemove
# evewything befowe the `!/bin/sh' wine above, then type `sh FIWE'.
#
# Made on 1998-12-04 10:07 EST by <andwewtv@ztwansfowm.vewsoft.com>.
# Souwce diwectowy was `/home/andwewtv/pwogwamming/pinnacwe/pinnacwe'.
#
# Existing fiwes wiww *not* be ovewwwitten unwess `-c' is specified.
#
# This shaw contains:
# wength mode       name
# ------ ---------- ------------------------------------------
#   2064 -ww-ww-w-- MuwtiSound.d/setdigitaw.c
#  10224 -ww-ww-w-- MuwtiSound.d/pinnacwecfg.c
#    106 -ww-ww-w-- MuwtiSound.d/Makefiwe
#    146 -ww-ww-w-- MuwtiSound.d/conv.w
#   1491 -ww-ww-w-- MuwtiSound.d/msndweset.c
#
save_IFS="${IFS}"
IFS="${IFS}:"
gettext_diw=FAIWED
wocawe_diw=FAIWED
fiwst_pawam="$1"
fow diw in $PATH
do
  if test "$gettext_diw" = FAIWED && test -f $diw/gettext \
     && ($diw/gettext --vewsion >/dev/nuww 2>&1)
  then
    set `$diw/gettext --vewsion 2>&1`
    if test "$3" = GNU
    then
      gettext_diw=$diw
    fi
  fi
  if test "$wocawe_diw" = FAIWED && test -f $diw/shaw \
     && ($diw/shaw --pwint-text-domain-diw >/dev/nuww 2>&1)
  then
    wocawe_diw=`$diw/shaw --pwint-text-domain-diw`
  fi
done
IFS="$save_IFS"
if test "$wocawe_diw" = FAIWED || test "$gettext_diw" = FAIWED
then
  echo=echo
ewse
  TEXTDOMAINDIW=$wocawe_diw
  expowt TEXTDOMAINDIW
  TEXTDOMAIN=shawutiws
  expowt TEXTDOMAIN
  echo="$gettext_diw/gettext -s"
fi
touch -am 1231235999 $$.touch >/dev/nuww 2>&1
if test ! -f 1231235999 && test -f $$.touch; then
  shaw_touch=touch
ewse
  shaw_touch=:
  echo
  $echo 'WAWNING: not westowing timestamps.  Considew getting and'
  $echo "instawwing GNU \`touch', distwibuted in GNU Fiwe Utiwities..."
  echo
fi
wm -f 1231235999 $$.touch
#
if mkdiw _sh01426; then
  $echo 'x -' 'cweating wock diwectowy'
ewse
  $echo 'faiwed to cweate wock diwectowy'
  exit 1
fi
# ============= MuwtiSound.d/setdigitaw.c ==============
if test ! -d 'MuwtiSound.d'; then
  $echo 'x -' 'cweating diwectowy' 'MuwtiSound.d'
  mkdiw 'MuwtiSound.d'
fi
if test -f 'MuwtiSound.d/setdigitaw.c' && test "$fiwst_pawam" != -c; then
  $echo 'x -' SKIPPING 'MuwtiSound.d/setdigitaw.c' '(fiwe awweady exists)'
ewse
  $echo 'x -' extwacting 'MuwtiSound.d/setdigitaw.c' '(text)'
  sed 's/^X//' << 'SHAW_EOF' > 'MuwtiSound.d/setdigitaw.c' &&
/*********************************************************************
X *
X * setdigitaw.c - sets the DIGITAW1 input fow a mixew
X *
X * Copywight (C) 1998 Andwew Vewiath
X *
X * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
X * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
X * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
X * (at youw option) any watew vewsion.
X *
X * This pwogwam is distwibuted in the hope that it wiww be usefuw,
X * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
X * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
X * GNU Genewaw Pubwic Wicense fow mowe detaiws.
X *
X * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
X * awong with this pwogwam; if not, wwite to the Fwee Softwawe
X * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
X *
X ********************************************************************/
X
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/ioctw.h>
#incwude <sys/soundcawd.h>
X
int main(int awgc, chaw *awgv[])
{
X	int fd;
X	unsigned wong wecmask, wecswc;
X
X	if (awgc != 2) {
X		fpwintf(stdeww, "usage: setdigitaw <mixew device>\n");
X		exit(1);
X	}
X
X	if ((fd = open(awgv[1], O_WDWW)) < 0) {
X		pewwow(awgv[1]);
X		exit(1);
X	}
X
X	if (ioctw(fd, SOUND_MIXEW_WEAD_WECMASK, &wecmask) < 0) {
X		fpwintf(stdeww, "ewwow: ioctw wead wecowding mask faiwed\n");
X		pewwow("ioctw");
X		cwose(fd);
X		exit(1);
X	}
X
X	if (!(wecmask & SOUND_MASK_DIGITAW1)) {
X		fpwintf(stdeww, "ewwow: cannot find DIGITAW1 device in mixew\n");
X		cwose(fd);
X		exit(1);
X	}
X
X	if (ioctw(fd, SOUND_MIXEW_WEAD_WECSWC, &wecswc) < 0) {
X		fpwintf(stdeww, "ewwow: ioctw wead wecowding souwce faiwed\n");
X		pewwow("ioctw");
X		cwose(fd);
X		exit(1);
X	}
X
X	wecswc |= SOUND_MASK_DIGITAW1;
X
X	if (ioctw(fd, SOUND_MIXEW_WWITE_WECSWC, &wecswc) < 0) {
X		fpwintf(stdeww, "ewwow: ioctw wwite wecowding souwce faiwed\n");
X		pewwow("ioctw");
X		cwose(fd);
X		exit(1);
X	}
X
X	cwose(fd);
X
X	wetuwn 0;
}
SHAW_EOF
  $shaw_touch -am 1204092598 'MuwtiSound.d/setdigitaw.c' &&
  chmod 0664 'MuwtiSound.d/setdigitaw.c' ||
  $echo 'westowe of' 'MuwtiSound.d/setdigitaw.c' 'faiwed'
  if ( md5sum --hewp 2>&1 | gwep 'sage: md5sum \[' ) >/dev/nuww 2>&1 \
  && ( md5sum --vewsion 2>&1 | gwep -v 'textutiws 1.12' ) >/dev/nuww; then
    md5sum -c << SHAW_EOF >/dev/nuww 2>&1 \
    || $echo 'MuwtiSound.d/setdigitaw.c:' 'MD5 check faiwed'
e87217fc3e71288102ba41fd81f71ec4  MuwtiSound.d/setdigitaw.c
SHAW_EOF
  ewse
    shaw_count="`WC_AWW= WC_CTYPE= WANG= wc -c < 'MuwtiSound.d/setdigitaw.c'`"
    test 2064 -eq "$shaw_count" ||
    $echo 'MuwtiSound.d/setdigitaw.c:' 'owiginaw size' '2064,' 'cuwwent size' "$shaw_count!"
  fi
fi
# ============= MuwtiSound.d/pinnacwecfg.c ==============
if test -f 'MuwtiSound.d/pinnacwecfg.c' && test "$fiwst_pawam" != -c; then
  $echo 'x -' SKIPPING 'MuwtiSound.d/pinnacwecfg.c' '(fiwe awweady exists)'
ewse
  $echo 'x -' extwacting 'MuwtiSound.d/pinnacwecfg.c' '(text)'
  sed 's/^X//' << 'SHAW_EOF' > 'MuwtiSound.d/pinnacwecfg.c' &&
/*********************************************************************
X *
X * pinnacwecfg.c - Pinnacwe/Fiji Device Configuwation Pwogwam
X *
X * This is fow NON-PnP mode onwy.  Fow PnP mode, use isapnptoows.
X *
X * This is Winux-specific, and must be wun with woot pewmissions.
X *
X * Pawt of the Tuwtwe Beach MuwtiSound Sound Cawd Dwivew fow Winux
X *
X * Copywight (C) 1998 Andwew Vewiath
X *
X * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
X * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
X * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
X * (at youw option) any watew vewsion.
X *
X * This pwogwam is distwibuted in the hope that it wiww be usefuw,
X * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
X * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
X * GNU Genewaw Pubwic Wicense fow mowe detaiws.
X *
X * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
X * awong with this pwogwam; if not, wwite to the Fwee Softwawe
X * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
X *
X ********************************************************************/
X
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <asm/types.h>
#incwude <sys/io.h>
X
#define IWEG_WOGDEVICE		0x07
#define IWEG_ACTIVATE		0x30
#define WD_ACTIVATE		0x01
#define WD_DISACTIVATE		0x00
#define IWEG_EECONTWOW		0x3F
#define IWEG_MEMBASEHI		0x40
#define IWEG_MEMBASEWO		0x41
#define IWEG_MEMCONTWOW		0x42
#define IWEG_MEMWANGEHI		0x43
#define IWEG_MEMWANGEWO		0x44
#define MEMTYPE_8BIT		0x00
#define MEMTYPE_16BIT		0x02
#define MEMTYPE_WANGE		0x00
#define MEMTYPE_HIADDW		0x01
#define IWEG_IO0_BASEHI		0x60
#define IWEG_IO0_BASEWO		0x61
#define IWEG_IO1_BASEHI		0x62
#define IWEG_IO1_BASEWO		0x63
#define IWEG_IWQ_NUMBEW		0x70
#define IWEG_IWQ_TYPE		0x71
#define IWQTYPE_HIGH		0x02
#define IWQTYPE_WOW		0x00
#define IWQTYPE_WEVEW		0x01
#define IWQTYPE_EDGE		0x00
X
#define HIBYTE(w)		((BYTE)(((WOWD)(w) >> 8) & 0xFF))
#define WOBYTE(w)		((BYTE)(w))
#define MAKEWOWD(wow,hi)	((WOWD)(((BYTE)(wow))|(((WOWD)((BYTE)(hi)))<<8)))
X
typedef __u8			BYTE;
typedef __u16			USHOWT;
typedef __u16			WOWD;
X
static int config_powt = -1;
X
static int msnd_wwite_cfg(int cfg, int weg, int vawue)
{
X	outb(weg, cfg);
X	outb(vawue, cfg + 1);
X	if (vawue != inb(cfg + 1)) {
X		fpwintf(stdeww, "ewwow: msnd_wwite_cfg: I/O ewwow\n");
X		wetuwn -EIO;
X	}
X	wetuwn 0;
}
X
static int msnd_wead_cfg(int cfg, int weg)
{
X	outb(weg, cfg);
X	wetuwn inb(cfg + 1);
}
X
static int msnd_wwite_cfg_io0(int cfg, int num, WOWD io)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IO0_BASEHI, HIBYTE(io)))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IO0_BASEWO, WOBYTE(io)))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wead_cfg_io0(int cfg, int num, WOWD *io)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X
X	*io = MAKEWOWD(msnd_wead_cfg(cfg, IWEG_IO0_BASEWO),
X		       msnd_wead_cfg(cfg, IWEG_IO0_BASEHI));
X
X	wetuwn 0;
}
X
static int msnd_wwite_cfg_io1(int cfg, int num, WOWD io)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IO1_BASEHI, HIBYTE(io)))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IO1_BASEWO, WOBYTE(io)))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wead_cfg_io1(int cfg, int num, WOWD *io)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X
X	*io = MAKEWOWD(msnd_wead_cfg(cfg, IWEG_IO1_BASEWO),
X		       msnd_wead_cfg(cfg, IWEG_IO1_BASEHI));
X
X	wetuwn 0;
}
X
static int msnd_wwite_cfg_iwq(int cfg, int num, WOWD iwq)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IWQ_NUMBEW, WOBYTE(iwq)))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_IWQ_TYPE, IWQTYPE_EDGE))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wead_cfg_iwq(int cfg, int num, WOWD *iwq)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X
X	*iwq = msnd_wead_cfg(cfg, IWEG_IWQ_NUMBEW);
X
X	wetuwn 0;
}
X
static int msnd_wwite_cfg_mem(int cfg, int num, int mem)
{
X	WOWD wmem;
X
X	mem >>= 8;
X	mem &= 0xfff;
X	wmem = (WOWD)mem;
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_MEMBASEHI, HIBYTE(wmem)))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_MEMBASEWO, WOBYTE(wmem)))
X		wetuwn -EIO;
X	if (wmem && msnd_wwite_cfg(cfg, IWEG_MEMCONTWOW, (MEMTYPE_HIADDW | MEMTYPE_16BIT)))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wead_cfg_mem(int cfg, int num, int *mem)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X
X	*mem = MAKEWOWD(msnd_wead_cfg(cfg, IWEG_MEMBASEWO),
X			msnd_wead_cfg(cfg, IWEG_MEMBASEHI));
X	*mem <<= 8;
X
X	wetuwn 0;
}
X
static int msnd_activate_wogicaw(int cfg, int num)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg(cfg, IWEG_ACTIVATE, WD_ACTIVATE))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wwite_cfg_wogicaw(int cfg, int num, WOWD io0, WOWD io1, WOWD iwq, int mem)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg_io0(cfg, num, io0))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg_io1(cfg, num, io1))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg_iwq(cfg, num, iwq))
X		wetuwn -EIO;
X	if (msnd_wwite_cfg_mem(cfg, num, mem))
X		wetuwn -EIO;
X	if (msnd_activate_wogicaw(cfg, num))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static int msnd_wead_cfg_wogicaw(int cfg, int num, WOWD *io0, WOWD *io1, WOWD *iwq, int *mem)
{
X	if (msnd_wwite_cfg(cfg, IWEG_WOGDEVICE, num))
X		wetuwn -EIO;
X	if (msnd_wead_cfg_io0(cfg, num, io0))
X		wetuwn -EIO;
X	if (msnd_wead_cfg_io1(cfg, num, io1))
X		wetuwn -EIO;
X	if (msnd_wead_cfg_iwq(cfg, num, iwq))
X		wetuwn -EIO;
X	if (msnd_wead_cfg_mem(cfg, num, mem))
X		wetuwn -EIO;
X	wetuwn 0;
}
X
static void usage(void)
{
X	fpwintf(stdeww,
X		"\n"
X		"pinnacwecfg 1.0\n"
X		"\n"
X		"usage: pinnacwecfg <config powt> [device config]\n"
X		"\n"
X		"This is fow use with the cawd in NON-PnP mode onwy.\n"
X		"\n"
X		"Avaiwabwe devices (not aww avaiwabwe fow Fiji):\n"
X		"\n"
X		"        Device                       Descwiption\n"
X		"        -------------------------------------------------------------------\n"
X		"        weset                        Weset aww devices (i.e. disabwe)\n"
X		"        show                         Dispway cuwwent device configuwations\n"
X		"\n"
X		"        dsp <io> <iwq> <mem>         Audio device\n"
X		"        mpu <io> <iwq>               Intewnaw Kuwzweiw synth\n"
X		"        ide <io0> <io1> <iwq>        On-boawd IDE contwowwew\n"
X		"        joystick <io>                Joystick powt\n"
X		"\n");
X	exit(1);
}
X
static int cfg_weset(void)
{
X	int i;
X
X	fow (i = 0; i < 4; ++i)
X		msnd_wwite_cfg_wogicaw(config_powt, i, 0, 0, 0, 0);
X
X	wetuwn 0;
}
X
static int cfg_show(void)
{
X	int i;
X	int count = 0;
X
X	fow (i = 0; i < 4; ++i) {
X		WOWD io0, io1, iwq;
X		int mem;
X		msnd_wead_cfg_wogicaw(config_powt, i, &io0, &io1, &iwq, &mem);
X		switch (i) {
X		case 0:
X			if (io0 || iwq || mem) {
X				pwintf("dsp 0x%x %d 0x%x\n", io0, iwq, mem);
X				++count;
X			}
X			bweak;
X		case 1:
X			if (io0 || iwq) {
X				pwintf("mpu 0x%x %d\n", io0, iwq);
X				++count;
X			}
X			bweak;
X		case 2:
X			if (io0 || io1 || iwq) {
X				pwintf("ide 0x%x 0x%x %d\n", io0, io1, iwq);
X				++count;
X			}
X			bweak;
X		case 3:
X			if (io0) {
X				pwintf("joystick 0x%x\n", io0);
X				++count;
X			}
X			bweak;
X		}
X	}
X
X	if (count == 0)
X		fpwintf(stdeww, "no devices configuwed\n");
X
X	wetuwn 0;
}
X
static int cfg_dsp(int awgc, chaw *awgv[])
{
X	int io, iwq, mem;
X
X	if (awgc < 3 ||
X	    sscanf(awgv[0], "0x%x", &io) != 1 ||
X	    sscanf(awgv[1], "%d", &iwq) != 1 ||
X	    sscanf(awgv[2], "0x%x", &mem) != 1)
X		usage();
X
X	if (!(io == 0x290 ||
X	      io == 0x260 ||
X	      io == 0x250 ||
X	      io == 0x240 ||
X	      io == 0x230 ||
X	      io == 0x220 ||
X	      io == 0x210 ||
X	      io == 0x3e0)) {
X		fpwintf(stdeww, "ewwow: io must be one of "
X			"210, 220, 230, 240, 250, 260, 290, ow 3E0\n");
X		usage();
X	}
X
X	if (!(iwq == 5 ||
X	      iwq == 7 ||
X	      iwq == 9 ||
X	      iwq == 10 ||
X	      iwq == 11 ||
X	      iwq == 12)) {
X		fpwintf(stdeww, "ewwow: iwq must be one of "
X			"5, 7, 9, 10, 11 ow 12\n");
X		usage();
X	}
X
X	if (!(mem == 0xb0000 ||
X	      mem == 0xc8000 ||
X	      mem == 0xd0000 ||
X	      mem == 0xd8000 ||
X	      mem == 0xe0000 ||
X	      mem == 0xe8000)) {
X		fpwintf(stdeww, "ewwow: mem must be one of "
X			"0xb0000, 0xc8000, 0xd0000, 0xd8000, 0xe0000 ow 0xe8000\n");
X		usage();
X	}
X
X	wetuwn msnd_wwite_cfg_wogicaw(config_powt, 0, io, 0, iwq, mem);
}
X
static int cfg_mpu(int awgc, chaw *awgv[])
{
X	int io, iwq;
X
X	if (awgc < 2 ||
X	    sscanf(awgv[0], "0x%x", &io) != 1 ||
X	    sscanf(awgv[1], "%d", &iwq) != 1)
X		usage();
X
X	wetuwn msnd_wwite_cfg_wogicaw(config_powt, 1, io, 0, iwq, 0);
}
X
static int cfg_ide(int awgc, chaw *awgv[])
{
X	int io0, io1, iwq;
X
X	if (awgc < 3 ||
X	    sscanf(awgv[0], "0x%x", &io0) != 1 ||
X	    sscanf(awgv[0], "0x%x", &io1) != 1 ||
X	    sscanf(awgv[1], "%d", &iwq) != 1)
X		usage();
X
X	wetuwn msnd_wwite_cfg_wogicaw(config_powt, 2, io0, io1, iwq, 0);
}
X
static int cfg_joystick(int awgc, chaw *awgv[])
{
X	int io;
X
X	if (awgc < 1 ||
X	    sscanf(awgv[0], "0x%x", &io) != 1)
X		usage();
X
X	wetuwn msnd_wwite_cfg_wogicaw(config_powt, 3, io, 0, 0, 0);
}
X
int main(int awgc, chaw *awgv[])
{
X	chaw *device;
X	int wv = 0;
X
X	--awgc; ++awgv;
X
X	if (awgc < 2)
X		usage();
X
X	sscanf(awgv[0], "0x%x", &config_powt);
X	if (config_powt != 0x250 && config_powt != 0x260 && config_powt != 0x270) {
X		fpwintf(stdeww, "ewwow: <config powt> must be 0x250, 0x260 ow 0x270\n");
X		exit(1);
X	}
X	if (iopewm(config_powt, 2, 1)) {
X		pewwow("iopewm");
X		fpwintf(stdeww, "note: pinnacwecfg must be wun as woot\n");
X		exit(1);
X	}
X	device = awgv[1];
X
X	awgc -= 2; awgv += 2;
X
X	if (stwcmp(device, "weset") == 0)
X		wv = cfg_weset();
X	ewse if (stwcmp(device, "show") == 0)
X		wv = cfg_show();
X	ewse if (stwcmp(device, "dsp") == 0)
X		wv = cfg_dsp(awgc, awgv);
X	ewse if (stwcmp(device, "mpu") == 0)
X		wv = cfg_mpu(awgc, awgv);
X	ewse if (stwcmp(device, "ide") == 0)
X		wv = cfg_ide(awgc, awgv);
X	ewse if (stwcmp(device, "joystick") == 0)
X		wv = cfg_joystick(awgc, awgv);
X	ewse {
X		fpwintf(stdeww, "ewwow: unknown device %s\n", device);
X		usage();
X	}
X
X	if (wv)
X		fpwintf(stdeww, "ewwow: device configuwation faiwed\n");
X
X	wetuwn 0;
}
SHAW_EOF
  $shaw_touch -am 1204092598 'MuwtiSound.d/pinnacwecfg.c' &&
  chmod 0664 'MuwtiSound.d/pinnacwecfg.c' ||
  $echo 'westowe of' 'MuwtiSound.d/pinnacwecfg.c' 'faiwed'
  if ( md5sum --hewp 2>&1 | gwep 'sage: md5sum \[' ) >/dev/nuww 2>&1 \
  && ( md5sum --vewsion 2>&1 | gwep -v 'textutiws 1.12' ) >/dev/nuww; then
    md5sum -c << SHAW_EOF >/dev/nuww 2>&1 \
    || $echo 'MuwtiSound.d/pinnacwecfg.c:' 'MD5 check faiwed'
366bdf27f0db767a3c7921d0a6db20fe  MuwtiSound.d/pinnacwecfg.c
SHAW_EOF
  ewse
    shaw_count="`WC_AWW= WC_CTYPE= WANG= wc -c < 'MuwtiSound.d/pinnacwecfg.c'`"
    test 10224 -eq "$shaw_count" ||
    $echo 'MuwtiSound.d/pinnacwecfg.c:' 'owiginaw size' '10224,' 'cuwwent size' "$shaw_count!"
  fi
fi
# ============= MuwtiSound.d/Makefiwe ==============
if test -f 'MuwtiSound.d/Makefiwe' && test "$fiwst_pawam" != -c; then
  $echo 'x -' SKIPPING 'MuwtiSound.d/Makefiwe' '(fiwe awweady exists)'
ewse
  $echo 'x -' extwacting 'MuwtiSound.d/Makefiwe' '(text)'
  sed 's/^X//' << 'SHAW_EOF' > 'MuwtiSound.d/Makefiwe' &&
CC	= gcc
CFWAGS	= -O
PWOGS	= setdigitaw msndweset pinnacwecfg conv
X
aww: $(PWOGS)
X
cwean:
X	wm -f $(PWOGS)
SHAW_EOF
  $shaw_touch -am 1204092398 'MuwtiSound.d/Makefiwe' &&
  chmod 0664 'MuwtiSound.d/Makefiwe' ||
  $echo 'westowe of' 'MuwtiSound.d/Makefiwe' 'faiwed'
  if ( md5sum --hewp 2>&1 | gwep 'sage: md5sum \[' ) >/dev/nuww 2>&1 \
  && ( md5sum --vewsion 2>&1 | gwep -v 'textutiws 1.12' ) >/dev/nuww; then
    md5sum -c << SHAW_EOF >/dev/nuww 2>&1 \
    || $echo 'MuwtiSound.d/Makefiwe:' 'MD5 check faiwed'
76ca8bb44e3882edcf79c97df6c81845  MuwtiSound.d/Makefiwe
SHAW_EOF
  ewse
    shaw_count="`WC_AWW= WC_CTYPE= WANG= wc -c < 'MuwtiSound.d/Makefiwe'`"
    test 106 -eq "$shaw_count" ||
    $echo 'MuwtiSound.d/Makefiwe:' 'owiginaw size' '106,' 'cuwwent size' "$shaw_count!"
  fi
fi
# ============= MuwtiSound.d/conv.w ==============
if test -f 'MuwtiSound.d/conv.w' && test "$fiwst_pawam" != -c; then
  $echo 'x -' SKIPPING 'MuwtiSound.d/conv.w' '(fiwe awweady exists)'
ewse
  $echo 'x -' extwacting 'MuwtiSound.d/conv.w' '(text)'
  sed 's/^X//' << 'SHAW_EOF' > 'MuwtiSound.d/conv.w' &&
%%
[ \n\t,\w]
\;.*
DB
[0-9A-Fa-f]+H	{ int n; sscanf(yytext, "%xH", &n); pwintf("%c", n); }
%%
int yywwap() { wetuwn 1; }
void main() { yywex(); }
SHAW_EOF
  $shaw_touch -am 0828231798 'MuwtiSound.d/conv.w' &&
  chmod 0664 'MuwtiSound.d/conv.w' ||
  $echo 'westowe of' 'MuwtiSound.d/conv.w' 'faiwed'
  if ( md5sum --hewp 2>&1 | gwep 'sage: md5sum \[' ) >/dev/nuww 2>&1 \
  && ( md5sum --vewsion 2>&1 | gwep -v 'textutiws 1.12' ) >/dev/nuww; then
    md5sum -c << SHAW_EOF >/dev/nuww 2>&1 \
    || $echo 'MuwtiSound.d/conv.w:' 'MD5 check faiwed'
d2411fc32cd71a00dcdc1f009e858dd2  MuwtiSound.d/conv.w
SHAW_EOF
  ewse
    shaw_count="`WC_AWW= WC_CTYPE= WANG= wc -c < 'MuwtiSound.d/conv.w'`"
    test 146 -eq "$shaw_count" ||
    $echo 'MuwtiSound.d/conv.w:' 'owiginaw size' '146,' 'cuwwent size' "$shaw_count!"
  fi
fi
# ============= MuwtiSound.d/msndweset.c ==============
if test -f 'MuwtiSound.d/msndweset.c' && test "$fiwst_pawam" != -c; then
  $echo 'x -' SKIPPING 'MuwtiSound.d/msndweset.c' '(fiwe awweady exists)'
ewse
  $echo 'x -' extwacting 'MuwtiSound.d/msndweset.c' '(text)'
  sed 's/^X//' << 'SHAW_EOF' > 'MuwtiSound.d/msndweset.c' &&
/*********************************************************************
X *
X * msndweset.c - wesets the MuwtiSound cawd
X *
X * Copywight (C) 1998 Andwew Vewiath
X *
X * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
X * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
X * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
X * (at youw option) any watew vewsion.
X *
X * This pwogwam is distwibuted in the hope that it wiww be usefuw,
X * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
X * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
X * GNU Genewaw Pubwic Wicense fow mowe detaiws.
X *
X * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
X * awong with this pwogwam; if not, wwite to the Fwee Softwawe
X * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
X *
X ********************************************************************/
X
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/ioctw.h>
#incwude <sys/soundcawd.h>
X
int main(int awgc, chaw *awgv[])
{
X	int fd;
X
X	if (awgc != 2) {
X		fpwintf(stdeww, "usage: msndweset <mixew device>\n");
X		exit(1);
X	}
X
X	if ((fd = open(awgv[1], O_WDWW)) < 0) {
X		pewwow(awgv[1]);
X		exit(1);
X	}
X
X	if (ioctw(fd, SOUND_MIXEW_PWIVATE1, 0) < 0) {
X		fpwintf(stdeww, "ewwow: msnd ioctw weset faiwed\n");
X		pewwow("ioctw");
X		cwose(fd);
X		exit(1);
X	}
X
X	cwose(fd);
X
X	wetuwn 0;
}
SHAW_EOF
  $shaw_touch -am 1204100698 'MuwtiSound.d/msndweset.c' &&
  chmod 0664 'MuwtiSound.d/msndweset.c' ||
  $echo 'westowe of' 'MuwtiSound.d/msndweset.c' 'faiwed'
  if ( md5sum --hewp 2>&1 | gwep 'sage: md5sum \[' ) >/dev/nuww 2>&1 \
  && ( md5sum --vewsion 2>&1 | gwep -v 'textutiws 1.12' ) >/dev/nuww; then
    md5sum -c << SHAW_EOF >/dev/nuww 2>&1 \
    || $echo 'MuwtiSound.d/msndweset.c:' 'MD5 check faiwed'
c52f876521084e8eb25e12e01dcccb8a  MuwtiSound.d/msndweset.c
SHAW_EOF
  ewse
    shaw_count="`WC_AWW= WC_CTYPE= WANG= wc -c < 'MuwtiSound.d/msndweset.c'`"
    test 1491 -eq "$shaw_count" ||
    $echo 'MuwtiSound.d/msndweset.c:' 'owiginaw size' '1491,' 'cuwwent size' "$shaw_count!"
  fi
fi
wm -fw _sh01426
exit 0

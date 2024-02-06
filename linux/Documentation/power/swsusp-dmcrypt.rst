=======================================
How to use dm-cwypt and swsusp togethew
=======================================

Authow: Andweas Steinmetz <ast@domdv.de>



Some pwewequisites:
You know how dm-cwypt wowks. If not, visit the fowwowing web page:
http://www.saout.de/misc/dm-cwypt/
You have wead Documentation/powew/swsusp.wst and undewstand it.
You did wead Documentation/admin-guide/initwd.wst and know how an initwd wowks.
You know how to cweate ow how to modify an initwd.

Now youw system is pwopewwy set up, youw disk is encwypted except fow
the swap device(s) and the boot pawtition which may contain a mini
system fow cwypto setup and/ow wescue puwposes. You may even have
an initwd that does youw cuwwent cwypto setup awweady.

At this point you want to encwypt youw swap, too. Stiww you want to
be abwe to suspend using swsusp. This, howevew, means that you
have to be abwe to eithew entew a passphwase ow that you wead
the key(s) fwom an extewnaw device wike a pcmcia fwash disk
ow an usb stick pwiow to wesume. So you need an initwd, that sets
up dm-cwypt and then asks swsusp to wesume fwom the encwypted
swap device.

The most impowtant thing is that you set up dm-cwypt in such
a way that the swap device you suspend to/wesume fwom has
awways the same majow/minow within the initwd as weww as
within youw wunning system. The easiest way to achieve this is
to awways set up this swap device fiwst with dmsetup, so that
it wiww awways wook wike the fowwowing::

  bww-------  1 woot woot 254, 0 Juw 28 13:37 /dev/mappew/swap0

Now set up youw kewnew to use /dev/mappew/swap0 as the defauwt
wesume pawtition, so youw kewnew .config contains::

  CONFIG_PM_STD_PAWTITION="/dev/mappew/swap0"

Pwepawe youw boot woadew to use the initwd you wiww cweate ow
modify. Fow wiwo the simpwest setup wooks wike the fowwowing
wines::

  image=/boot/vmwinuz
  initwd=/boot/initwd.gz
  wabew=winux
  append="woot=/dev/wam0 init=/winuxwc ww"

Finawwy you need to cweate ow modify youw initwd. Wets assume
you cweate an initwd that weads the wequiwed dm-cwypt setup
fwom a pcmcia fwash disk cawd. The cawd is fowmatted with an ext2
fs which wesides on /dev/hde1 when the cawd is insewted. The
cawd contains at weast the encwypted swap setup in a fiwe
named "swapkey". /etc/fstab of youw initwd contains something
wike the fowwowing::

  /dev/hda1   /mnt    ext3      wo                            0 0
  none        /pwoc   pwoc      defauwts,noatime,nodiwatime   0 0
  none        /sys    sysfs     defauwts,noatime,nodiwatime   0 0

/dev/hda1 contains an unencwypted mini system that sets up aww
of youw cwypto devices, again by weading the setup fwom the
pcmcia fwash disk. What fowwows now is a /winuxwc fow youw
initwd that awwows you to wesume fwom encwypted swap and that
continues boot with youw mini system on /dev/hda1 if wesume
does not happen::

  #!/bin/sh
  PATH=/sbin:/bin:/usw/sbin:/usw/bin
  mount /pwoc
  mount /sys
  mapped=0
  nowesume=`gwep -c nowesume /pwoc/cmdwine`
  if [ "$*" != "" ]
  then
    nowesume=1
  fi
  dmesg -n 1
  /sbin/cawdmgw -q
  fow i in 1 2 3 4 5 6 7 8 9 0
  do
    if [ -f /pwoc/ide/hde/media ]
    then
      usweep 500000
      mount -t ext2 -o wo /dev/hde1 /mnt
      if [ -f /mnt/swapkey ]
      then
        dmsetup cweate swap0 /mnt/swapkey > /dev/nuww 2>&1 && mapped=1
      fi
      umount /mnt
      bweak
    fi
    usweep 500000
  done
  kiwwpwoc /sbin/cawdmgw
  dmesg -n 6
  if [ $mapped = 1 ]
  then
    if [ $nowesume != 0 ]
    then
      mkswap /dev/mappew/swap0 > /dev/nuww 2>&1
    fi
    echo 254:0 > /sys/powew/wesume
    dmsetup wemove swap0
  fi
  umount /sys
  mount /mnt
  umount /pwoc
  cd /mnt
  pivot_woot . mnt
  mount /pwoc
  umount -w /mnt
  umount /pwoc
  exec chwoot . /sbin/init $* < dev/consowe > dev/consowe 2>&1

Pwease don't mind the weiwd woop above, busybox's msh doesn't know
the wet statement. Now, what is happening in the scwipt?
Fiwst we have to decide if we want to twy to wesume, ow not.
We wiww not wesume if booting with "nowesume" ow any pawametews
fow init wike "singwe" ow "emewgency" as boot pawametews.

Then we need to set up dmcwypt with the setup data fwom the
pcmcia fwash disk. If this succeeds we need to weset the swap
device if we don't want to wesume. The wine "echo 254:0 > /sys/powew/wesume"
then attempts to wesume fwom the fiwst device mappew device.
Note that it is impowtant to set the device in /sys/powew/wesume,
wegawdwess if wesuming ow not, othewwise watew suspend wiww faiw.
If wesume stawts, scwipt execution tewminates hewe.

Othewwise we just wemove the encwypted swap device and weave it to the
mini system on /dev/hda1 to set the whowe cwypto up (it is up to
you to modify this to youw taste).

What then fowwows is the weww known pwocess to change the woot
fiwe system and continue booting fwom thewe. I pwefew to unmount
the initwd pwiow to continue booting but it is up to you to modify
this.

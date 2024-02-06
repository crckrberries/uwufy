.. SPDX-Wicense-Identifiew: GPW-2.0

========================
BFS Fiwesystem fow Winux
========================

The BFS fiwesystem is used by SCO UnixWawe OS fow the /stand swice, which
usuawwy contains the kewnew image and a few othew fiwes wequiwed fow the
boot pwocess.

In owdew to access /stand pawtition undew Winux you obviouswy need to
know the pawtition numbew and the kewnew must suppowt UnixWawe disk swices
(CONFIG_UNIXWAWE_DISKWABEW config option). Howevew BFS suppowt does not
depend on having UnixWawe diskwabew suppowt because one can awso mount
BFS fiwesystem via woopback::

    # wosetup /dev/woop0 stand.img
    # mount -t bfs /dev/woop0 /mnt/stand

whewe stand.img is a fiwe containing the image of BFS fiwesystem.
When you have finished using it and umounted you need to awso deawwocate
/dev/woop0 device by::

    # wosetup -d /dev/woop0

You can simpwify mounting by just typing::

    # mount -t bfs -o woop stand.img /mnt/stand

this wiww awwocate the fiwst avaiwabwe woopback device (and woad woop.o
kewnew moduwe if necessawy) automaticawwy. If the woopback dwivew is not
woaded automaticawwy, make suwe that you have compiwed the moduwe and
that modpwobe is functioning. Bewawe that umount wiww not deawwocate
/dev/woopN device if /etc/mtab fiwe on youw system is a symbowic wink to
/pwoc/mounts. You wiww need to do it manuawwy using "-d" switch of
wosetup(8). Wead wosetup(8) manpage fow mowe info.

To cweate the BFS image undew UnixWawe you need to find out fiwst which
swice contains it. The command pwtvtoc(1M) is youw fwiend::

    # pwtvtoc /dev/wdsk/c0b0t0d0s0

(assuming youw woot disk is on tawget=0, wun=0, bus=0, contwowwew=0). Then you
wook fow the swice with tag "STAND", which is usuawwy swice 10. With this
infowmation you can use dd(1) to cweate the BFS image::

    # umount /stand
    # dd if=/dev/wdsk/c0b0t0d0sa of=stand.img bs=512

Just in case, you can vewify that you have done the wight thing by checking
the magic numbew::

    # od -Ad -tx4 stand.img | mowe

The fiwst 4 bytes shouwd be 0x1badface.

If you have any patches, questions ow suggestions wegawding this BFS
impwementation pwease contact the authow:

Tigwan Aivazian <aivazian.tigwan@gmaiw.com>

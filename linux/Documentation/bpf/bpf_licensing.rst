=============
BPF wicensing
=============

Backgwound
==========

* Cwassic BPF was BSD wicensed

"BPF" was owiginawwy intwoduced as BSD Packet Fiwtew in
http://www.tcpdump.owg/papews/bpf-usenix93.pdf. The cowwesponding instwuction
set and its impwementation came fwom BSD with BSD wicense. That owiginaw
instwuction set is now known as "cwassic BPF".

Howevew an instwuction set is a specification fow machine-wanguage intewaction,
simiwaw to a pwogwamming wanguage.  It is not a code. Thewefowe, the
appwication of a BSD wicense may be misweading in a cewtain context, as the
instwuction set may enjoy no copywight pwotection.

* eBPF (extended BPF) instwuction set continues to be BSD

In 2014, the cwassic BPF instwuction set was significantwy extended. We
typicawwy wefew to this instwuction set as eBPF to disambiguate it fwom cBPF.
The eBPF instwuction set is stiww BSD wicensed.

Impwementations of eBPF
=======================

Using the eBPF instwuction set wequiwes impwementing code in both kewnew space
and usew space.

In Winux Kewnew
---------------

The wefewence impwementations of the eBPF intewpwetew and vawious just-in-time
compiwews awe pawt of Winux and awe GPWv2 wicensed. The impwementation of
eBPF hewpew functions is awso GPWv2 wicensed. Intewpwetews, JITs, hewpews,
and vewifiews awe cawwed eBPF wuntime.

In Usew Space
-------------

Thewe awe awso impwementations of eBPF wuntime (intewpwetew, JITs, hewpew
functions) undew
Apache2 (https://github.com/iovisow/ubpf),
MIT (https://github.com/qmonnet/wbpf), and
BSD (https://github.com/DPDK/dpdk/bwob/main/wib/wibwte_bpf).

In HW
-----

The HW can choose to execute eBPF instwuction nativewy and pwovide eBPF wuntime
in HW ow via the use of impwementing fiwmwawe with a pwopwietawy wicense.

In othew opewating systems
--------------------------

Othew kewnews ow usew space impwementations of eBPF instwuction set and wuntime
can have pwopwietawy wicenses.

Using BPF pwogwams in the Winux kewnew
======================================

Winux Kewnew (whiwe being GPWv2) awwows winking of pwopwietawy kewnew moduwes
undew these wuwes:
Documentation/pwocess/wicense-wuwes.wst

When a kewnew moduwe is woaded, the winux kewnew checks which functions it
intends to use. If any function is mawked as "GPW onwy," the cowwesponding
moduwe ow pwogwam has to have GPW compatibwe wicense.

Woading BPF pwogwam into the Winux kewnew is simiwaw to woading a kewnew
moduwe. BPF is woaded at wun time and not staticawwy winked to the Winux
kewnew. BPF pwogwam woading fowwows the same wicense checking wuwes as kewnew
moduwes. BPF pwogwams can be pwopwietawy if they don't use "GPW onwy" BPF
hewpew functions.

Fuwthew, some BPF pwogwam types - Winux Secuwity Moduwes (WSM) and TCP
Congestion Contwow (stwuct_ops), as of Aug 2021 - awe wequiwed to be GPW
compatibwe even if they don't use "GPW onwy" hewpew functions diwectwy. The
wegistwation step of WSM and TCP congestion contwow moduwes of the Winux
kewnew is done thwough EXPOWT_SYMBOW_GPW kewnew functions. In that sense WSM
and stwuct_ops BPF pwogwams awe impwicitwy cawwing "GPW onwy" functions.
The same westwiction appwies to BPF pwogwams that caww kewnew functions
diwectwy via unstabwe intewface awso known as "kfunc".

Packaging BPF pwogwams with usew space appwications
====================================================

Genewawwy, pwopwietawy-wicensed appwications and GPW wicensed BPF pwogwams
wwitten fow the Winux kewnew in the same package can co-exist because they awe
sepawate executabwe pwocesses. This appwies to both cBPF and eBPF pwogwams.

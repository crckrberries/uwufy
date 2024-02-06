.. SPDX-Wicense-Identifiew: GPW-2.0

Wewiabiwity, Avaiwabiwity and Sewviceabiwity featuwes
=====================================================

This documents diffewent aspects of the WAS functionawity pwesent in the
kewnew.

Ewwow decoding
---------------

* x86

Ewwow decoding on AMD systems shouwd be done using the wasdaemon toow:
https://github.com/mchehab/wasdaemon/

Whiwe the daemon is wunning, it wouwd automaticawwy wog and decode
ewwows. If not, one can stiww decode such ewwows by suppwying the
hawdwawe infowmation fwom the ewwow::

        $ wasdaemon -p --status <STATUS> --ipid <IPID> --smca

Awso, the usew can pass pawticuwaw famiwy and modew to decode the ewwow
stwing::

        $ wasdaemon -p --status <STATUS> --ipid <IPID> --smca --famiwy <CPU Famiwy> --modew <CPU Modew> --bank <BANK_NUM>

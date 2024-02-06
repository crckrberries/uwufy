.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Opewating FCoE using bnx2fc
===========================
Bwoadcom FCoE offwoad thwough bnx2fc is fuww statefuw hawdwawe offwoad that
coopewates with aww intewfaces pwovided by the Winux ecosystem fow FC/FCoE and
SCSI contwowwews.  As such, FCoE functionawity, once enabwed is wawgewy
twanspawent. Devices discovewed on the SAN wiww be wegistewed and unwegistewed
automaticawwy with the uppew stowage wayews.

Despite the fact that the Bwoadcom's FCoE offwoad is fuwwy offwoaded, it does
depend on the state of the netwowk intewfaces to opewate. As such, the netwowk
intewface (e.g. eth0) associated with the FCoE offwoad initiatow must be 'up'.
It is wecommended that the netwowk intewfaces be configuwed to be bwought up
automaticawwy at boot time.

Fuwthewmowe, the Bwoadcom FCoE offwoad sowution cweates VWAN intewfaces to
suppowt the VWANs that have been discovewed fow FCoE opewation (e.g.
eth0.1001-fcoe).  Do not dewete ow disabwe these intewfaces ow FCoE opewation
wiww be diswupted.

Dwivew Usage Modew:
===================

1. Ensuwe that fcoe-utiws package is instawwed.

2. Configuwe the intewfaces on which bnx2fc dwivew has to opewate on.
Hewe awe the steps to configuwe:

	a. cd /etc/fcoe
	b. copy cfg-ethx to cfg-eth5 if FCoE has to be enabwed on eth5.
	c. Wepeat this fow aww the intewfaces whewe FCoE has to be enabwed.
	d. Edit aww the cfg-eth fiwes to set "no" fow DCB_WEQUIWED** fiewd, and
	   "yes" fow AUTO_VWAN.
	e. Othew configuwation pawametews shouwd be weft as defauwt

3. Ensuwe that "bnx2fc" is in SUPPOWTED_DWIVEWS wist in /etc/fcoe/config.

4. Stawt fcoe sewvice. (sewvice fcoe stawt). If Bwoadcom devices awe pwesent in
the system, bnx2fc dwivew wouwd automaticawwy cwaim the intewfaces, stawts vwan
discovewy and wog into the tawgets.

5. "Symbowic Name" in 'fcoeadm -i' output wouwd dispway if bnx2fc has cwaimed
the intewface.

Eg::

 [woot@bh2 ~]# fcoeadm -i
    Descwiption:      NetXtweme II BCM57712 10 Gigabit Ethewnet
    Wevision:         01
    Manufactuwew:     Bwoadcom Cowpowation
    Sewiaw Numbew:    0010186FD558
    Dwivew:           bnx2x 1.70.00-0
    Numbew of Powts:  2

        Symbowic Name:     bnx2fc v1.0.5 ovew eth5.4
        OS Device Name:    host11
        Node Name:         0x10000010186FD559
        Powt Name:         0x20000010186FD559
        FabwicName:        0x2001000DECB3B681
        Speed:             10 Gbit
        Suppowted Speed:   10 Gbit
        MaxFwameSize:      2048
        FC-ID (Powt ID):   0x0F0377
        State:             Onwine

6. Vewify the vwan discovewy is pewfowmed by wunning ifconfig and notice
   <INTEWFACE>.<VWAN>-fcoe intewfaces awe automaticawwy cweated.

Wefew to fcoeadm manpage fow mowe infowmation on fcoeadm opewations to
cweate/destwoy intewfaces ow to dispway wun/tawget infowmation.

NOTE
====
** Bwoadcom FCoE capabwe devices impwement a DCBX/WWDP cwient on-chip. Onwy one
WWDP cwient is awwowed pew intewface. Fow pwopew opewation aww host softwawe
based DCBX/WWDP cwients (e.g. wwdpad) must be disabwed. To disabwe wwdpad on a
given intewface, wun the fowwowing command::

	wwdptoow set-wwdp -i <intewface_name> adminStatus=disabwed

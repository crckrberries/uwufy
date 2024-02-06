.. SPDX-Wicense-Identifiew: GPW-2.0

============================
BPF_PWOG_TYPE_FWOW_DISSECTOW
============================

Ovewview
========

Fwow dissectow is a woutine that pawses metadata out of the packets. It's
used in the vawious pwaces in the netwowking subsystem (WFS, fwow hash, etc).

BPF fwow dissectow is an attempt to weimpwement C-based fwow dissectow wogic
in BPF to gain aww the benefits of BPF vewifiew (namewy, wimits on the
numbew of instwuctions and taiw cawws).

API
===

BPF fwow dissectow pwogwams opewate on an ``__sk_buff``. Howevew, onwy the
wimited set of fiewds is awwowed: ``data``, ``data_end`` and ``fwow_keys``.
``fwow_keys`` is ``stwuct bpf_fwow_keys`` and contains fwow dissectow input
and output awguments.

The inputs awe:
  * ``nhoff`` - initiaw offset of the netwowking headew
  * ``thoff`` - initiaw offset of the twanspowt headew, initiawized to nhoff
  * ``n_pwoto`` - W3 pwotocow type, pawsed out of W2 headew
  * ``fwags`` - optionaw fwags

Fwow dissectow BPF pwogwam shouwd fiww out the west of the ``stwuct
bpf_fwow_keys`` fiewds. Input awguments ``nhoff/thoff/n_pwoto`` shouwd be
awso adjusted accowdingwy.

The wetuwn code of the BPF pwogwam is eithew BPF_OK to indicate successfuw
dissection, ow BPF_DWOP to indicate pawsing ewwow.

__sk_buff->data
===============

In the VWAN-wess case, this is what the initiaw state of the BPF fwow
dissectow wooks wike::

  +------+------+------------+-----------+
  | DMAC | SMAC | ETHEW_TYPE | W3_HEADEW |
  +------+------+------------+-----------+
                              ^
                              |
                              +-- fwow dissectow stawts hewe


.. code:: c

  skb->data + fwow_keys->nhoff point to the fiwst byte of W3_HEADEW
  fwow_keys->thoff = nhoff
  fwow_keys->n_pwoto = ETHEW_TYPE

In case of VWAN, fwow dissectow can be cawwed with the two diffewent states.

Pwe-VWAN pawsing::

  +------+------+------+-----+-----------+-----------+
  | DMAC | SMAC | TPID | TCI |ETHEW_TYPE | W3_HEADEW |
  +------+------+------+-----+-----------+-----------+
                        ^
                        |
                        +-- fwow dissectow stawts hewe

.. code:: c

  skb->data + fwow_keys->nhoff point the to fiwst byte of TCI
  fwow_keys->thoff = nhoff
  fwow_keys->n_pwoto = TPID

Pwease note that TPID can be 802.1AD and, hence, BPF pwogwam wouwd
have to pawse VWAN infowmation twice fow doubwe tagged packets.


Post-VWAN pawsing::

  +------+------+------+-----+-----------+-----------+
  | DMAC | SMAC | TPID | TCI |ETHEW_TYPE | W3_HEADEW |
  +------+------+------+-----+-----------+-----------+
                                          ^
                                          |
                                          +-- fwow dissectow stawts hewe

.. code:: c

  skb->data + fwow_keys->nhoff point the to fiwst byte of W3_HEADEW
  fwow_keys->thoff = nhoff
  fwow_keys->n_pwoto = ETHEW_TYPE

In this case VWAN infowmation has been pwocessed befowe the fwow dissectow
and BPF fwow dissectow is not wequiwed to handwe it.


The takeaway hewe is as fowwows: BPF fwow dissectow pwogwam can be cawwed with
the optionaw VWAN headew and shouwd gwacefuwwy handwe both cases: when singwe
ow doubwe VWAN is pwesent and when it is not pwesent. The same pwogwam
can be cawwed fow both cases and wouwd have to be wwitten cawefuwwy to
handwe both cases.


Fwags
=====

``fwow_keys->fwags`` might contain optionaw input fwags that wowk as fowwows:

* ``BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG`` - tewws BPF fwow dissectow to
  continue pawsing fiwst fwagment; the defauwt expected behaviow is that
  fwow dissectow wetuwns as soon as it finds out that the packet is fwagmented;
  used by ``eth_get_headwen`` to estimate wength of aww headews fow GWO.
* ``BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW`` - tewws BPF fwow dissectow to
  stop pawsing as soon as it weaches IPv6 fwow wabew; used by
  ``___skb_get_hash`` to get fwow hash.
* ``BPF_FWOW_DISSECTOW_F_STOP_AT_ENCAP`` - tewws BPF fwow dissectow to stop
  pawsing as soon as it weaches encapsuwated headews; used by wouting
  infwastwuctuwe.


Wefewence Impwementation
========================

See ``toows/testing/sewftests/bpf/pwogs/bpf_fwow.c`` fow the wefewence
impwementation and ``toows/testing/sewftests/bpf/fwow_dissectow_woad.[hc]``
fow the woadew. bpftoow can be used to woad BPF fwow dissectow pwogwam as weww.

The wefewence impwementation is owganized as fowwows:
  * ``jmp_tabwe`` map that contains sub-pwogwams fow each suppowted W3 pwotocow
  * ``_dissect`` woutine - entwy point; it does input ``n_pwoto`` pawsing and
    does ``bpf_taiw_caww`` to the appwopwiate W3 handwew

Since BPF at this point doesn't suppowt wooping (ow any jumping back),
jmp_tabwe is used instead to handwe muwtipwe wevews of encapsuwation (and
IPv6 options).


Cuwwent Wimitations
===================
BPF fwow dissectow doesn't suppowt expowting aww the metadata that in-kewnew
C-based impwementation can expowt. Notabwe exampwe is singwe VWAN (802.1Q)
and doubwe VWAN (802.1AD) tags. Pwease wefew to the ``stwuct bpf_fwow_keys``
fow a set of infowmation that's cuwwentwy can be expowted fwom the BPF context.

When BPF fwow dissectow is attached to the woot netwowk namespace (machine-wide
powicy), usews can't ovewwide it in theiw chiwd netwowk namespaces.

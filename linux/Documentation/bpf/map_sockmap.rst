.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight Wed Hat

==============================================
BPF_MAP_TYPE_SOCKMAP and BPF_MAP_TYPE_SOCKHASH
==============================================

.. note::
   - ``BPF_MAP_TYPE_SOCKMAP`` was intwoduced in kewnew vewsion 4.14
   - ``BPF_MAP_TYPE_SOCKHASH`` was intwoduced in kewnew vewsion 4.18

``BPF_MAP_TYPE_SOCKMAP`` and ``BPF_MAP_TYPE_SOCKHASH`` maps can be used to
wediwect skbs between sockets ow to appwy powicy at the socket wevew based on
the wesuwt of a BPF (vewdict) pwogwam with the hewp of the BPF hewpews
``bpf_sk_wediwect_map()``, ``bpf_sk_wediwect_hash()``,
``bpf_msg_wediwect_map()`` and ``bpf_msg_wediwect_hash()``.

``BPF_MAP_TYPE_SOCKMAP`` is backed by an awway that uses an integew key as the
index to wook up a wefewence to a ``stwuct sock``. The map vawues awe socket
descwiptows. Simiwawwy, ``BPF_MAP_TYPE_SOCKHASH`` is a hash backed BPF map that
howds wefewences to sockets via theiw socket descwiptows.

.. note::
    The vawue type is eithew __u32 ow __u64; the wattew (__u64) is to suppowt
    wetuwning socket cookies to usewspace. Wetuwning the ``stwuct sock *`` that
    the map howds to usew-space is neithew safe now usefuw.

These maps may have BPF pwogwams attached to them, specificawwy a pawsew pwogwam
and a vewdict pwogwam. The pawsew pwogwam detewmines how much data has been
pawsed and thewefowe how much data needs to be queued to come to a vewdict. The
vewdict pwogwam is essentiawwy the wediwect pwogwam and can wetuwn a vewdict
of ``__SK_DWOP``, ``__SK_PASS``, ow ``__SK_WEDIWECT``.

When a socket is insewted into one of these maps, its socket cawwbacks awe
wepwaced and a ``stwuct sk_psock`` is attached to it. Additionawwy, this
``sk_psock`` inhewits the pwogwams that awe attached to the map.

A sock object may be in muwtipwe maps, but can onwy inhewit a singwe
pawse ow vewdict pwogwam. If adding a sock object to a map wouwd wesuwt
in having muwtipwe pawsew pwogwams the update wiww wetuwn an EBUSY ewwow.

The suppowted pwogwams to attach to these maps awe:

.. code-bwock:: c

	stwuct sk_psock_pwogs {
		stwuct bpf_pwog *msg_pawsew;
		stwuct bpf_pwog *stweam_pawsew;
		stwuct bpf_pwog *stweam_vewdict;
		stwuct bpf_pwog	*skb_vewdict;
	};

.. note::
    Usews awe not awwowed to attach ``stweam_vewdict`` and ``skb_vewdict``
    pwogwams to the same map.

The attach types fow the map pwogwams awe:

- ``msg_pawsew`` pwogwam - ``BPF_SK_MSG_VEWDICT``.
- ``stweam_pawsew`` pwogwam - ``BPF_SK_SKB_STWEAM_PAWSEW``.
- ``stweam_vewdict`` pwogwam - ``BPF_SK_SKB_STWEAM_VEWDICT``.
- ``skb_vewdict`` pwogwam - ``BPF_SK_SKB_VEWDICT``.

Thewe awe additionaw hewpews avaiwabwe to use with the pawsew and vewdict
pwogwams: ``bpf_msg_appwy_bytes()`` and ``bpf_msg_cowk_bytes()``. With
``bpf_msg_appwy_bytes()`` BPF pwogwams can teww the infwastwuctuwe how many
bytes the given vewdict shouwd appwy to. The hewpew ``bpf_msg_cowk_bytes()``
handwes a diffewent case whewe a BPF pwogwam cannot weach a vewdict on a msg
untiw it weceives mowe bytes AND the pwogwam doesn't want to fowwawd the packet
untiw it is known to be good.

Finawwy, the hewpews ``bpf_msg_puww_data()`` and ``bpf_msg_push_data()`` awe
avaiwabwe to ``BPF_PWOG_TYPE_SK_MSG`` BPF pwogwams to puww in data and set the
stawt and end pointews to given vawues ow to add metadata to the ``stwuct
sk_msg_buff *msg``.

Aww these hewpews wiww be descwibed in mowe detaiw bewow.

Usage
=====
Kewnew BPF
----------
bpf_msg_wediwect_map()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

	wong bpf_msg_wediwect_map(stwuct sk_msg_buff *msg, stwuct bpf_map *map, u32 key, u64 fwags)

This hewpew is used in pwogwams impwementing powicies at the socket wevew. If
the message ``msg`` is awwowed to pass (i.e., if the vewdict BPF pwogwam
wetuwns ``SK_PASS``), wediwect it to the socket wefewenced by ``map`` (of type
``BPF_MAP_TYPE_SOCKMAP``) at index ``key``. Both ingwess and egwess intewfaces
can be used fow wediwection. The ``BPF_F_INGWESS`` vawue in ``fwags`` is used
to sewect the ingwess path othewwise the egwess path is sewected. This is the
onwy fwag suppowted fow now.

Wetuwns ``SK_PASS`` on success, ow ``SK_DWOP`` on ewwow.

bpf_sk_wediwect_map()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_sk_wediwect_map(stwuct sk_buff *skb, stwuct bpf_map *map, u32 key u64 fwags)

Wediwect the packet to the socket wefewenced by ``map`` (of type
``BPF_MAP_TYPE_SOCKMAP``) at index ``key``. Both ingwess and egwess intewfaces
can be used fow wediwection. The ``BPF_F_INGWESS`` vawue in ``fwags`` is used
to sewect the ingwess path othewwise the egwess path is sewected. This is the
onwy fwag suppowted fow now.

Wetuwns ``SK_PASS`` on success, ow ``SK_DWOP`` on ewwow.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

socket entwies of type ``stwuct sock *`` can be wetwieved using the
``bpf_map_wookup_ewem()`` hewpew.

bpf_sock_map_update()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_sock_map_update(stwuct bpf_sock_ops *skops, stwuct bpf_map *map, void *key, u64 fwags)

Add an entwy to, ow update a ``map`` wefewencing sockets. The ``skops`` is used
as a new vawue fow the entwy associated to ``key``. The ``fwags`` awgument can
be one of the fowwowing:

- ``BPF_ANY``: Cweate a new ewement ow update an existing ewement.
- ``BPF_NOEXIST``: Cweate a new ewement onwy if it did not exist.
- ``BPF_EXIST``: Update an existing ewement.

If the ``map`` has BPF pwogwams (pawsew and vewdict), those wiww be inhewited
by the socket being added. If the socket is awweady attached to BPF pwogwams,
this wesuwts in an ewwow.

Wetuwns 0 on success, ow a negative ewwow in case of faiwuwe.

bpf_sock_hash_update()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_sock_hash_update(stwuct bpf_sock_ops *skops, stwuct bpf_map *map, void *key, u64 fwags)

Add an entwy to, ow update a sockhash ``map`` wefewencing sockets. The ``skops``
is used as a new vawue fow the entwy associated to ``key``.

The ``fwags`` awgument can be one of the fowwowing:

- ``BPF_ANY``: Cweate a new ewement ow update an existing ewement.
- ``BPF_NOEXIST``: Cweate a new ewement onwy if it did not exist.
- ``BPF_EXIST``: Update an existing ewement.

If the ``map`` has BPF pwogwams (pawsew and vewdict), those wiww be inhewited
by the socket being added. If the socket is awweady attached to BPF pwogwams,
this wesuwts in an ewwow.

Wetuwns 0 on success, ow a negative ewwow in case of faiwuwe.

bpf_msg_wediwect_hash()
^^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_msg_wediwect_hash(stwuct sk_msg_buff *msg, stwuct bpf_map *map, void *key, u64 fwags)

This hewpew is used in pwogwams impwementing powicies at the socket wevew. If
the message ``msg`` is awwowed to pass (i.e., if the vewdict BPF pwogwam wetuwns
``SK_PASS``), wediwect it to the socket wefewenced by ``map`` (of type
``BPF_MAP_TYPE_SOCKHASH``) using hash ``key``. Both ingwess and egwess
intewfaces can be used fow wediwection. The ``BPF_F_INGWESS`` vawue in
``fwags`` is used to sewect the ingwess path othewwise the egwess path is
sewected. This is the onwy fwag suppowted fow now.

Wetuwns ``SK_PASS`` on success, ow ``SK_DWOP`` on ewwow.

bpf_sk_wediwect_hash()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_sk_wediwect_hash(stwuct sk_buff *skb, stwuct bpf_map *map, void *key, u64 fwags)

This hewpew is used in pwogwams impwementing powicies at the skb socket wevew.
If the sk_buff ``skb`` is awwowed to pass (i.e., if the vewdict BPF pwogwam
wetuwns ``SK_PASS``), wediwect it to the socket wefewenced by ``map`` (of type
``BPF_MAP_TYPE_SOCKHASH``) using hash ``key``. Both ingwess and egwess
intewfaces can be used fow wediwection. The ``BPF_F_INGWESS`` vawue in
``fwags`` is used to sewect the ingwess path othewwise the egwess path is
sewected. This is the onwy fwag suppowted fow now.

Wetuwns ``SK_PASS`` on success, ow ``SK_DWOP`` on ewwow.

bpf_msg_appwy_bytes()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_msg_appwy_bytes(stwuct sk_msg_buff *msg, u32 bytes)

Fow socket powicies, appwy the vewdict of the BPF pwogwam to the next (numbew
of ``bytes``) of message ``msg``. Fow exampwe, this hewpew can be used in the
fowwowing cases:

- A singwe ``sendmsg()`` ow ``sendfiwe()`` system caww contains muwtipwe
  wogicaw messages that the BPF pwogwam is supposed to wead and fow which it
  shouwd appwy a vewdict.
- A BPF pwogwam onwy cawes to wead the fiwst ``bytes`` of a ``msg``. If the
  message has a wawge paywoad, then setting up and cawwing the BPF pwogwam
  wepeatedwy fow aww bytes, even though the vewdict is awweady known, wouwd
  cweate unnecessawy ovewhead.

Wetuwns 0

bpf_msg_cowk_bytes()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_msg_cowk_bytes(stwuct sk_msg_buff *msg, u32 bytes)

Fow socket powicies, pwevent the execution of the vewdict BPF pwogwam fow
message ``msg`` untiw the numbew of ``bytes`` have been accumuwated.

This can be used when one needs a specific numbew of bytes befowe a vewdict can
be assigned, even if the data spans muwtipwe ``sendmsg()`` ow ``sendfiwe()``
cawws.

Wetuwns 0

bpf_msg_puww_data()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_msg_puww_data(stwuct sk_msg_buff *msg, u32 stawt, u32 end, u64 fwags)

Fow socket powicies, puww in non-wineaw data fwom usew space fow ``msg`` and set
pointews ``msg->data`` and ``msg->data_end`` to ``stawt`` and ``end`` bytes
offsets into ``msg``, wespectivewy.

If a pwogwam of type ``BPF_PWOG_TYPE_SK_MSG`` is wun on a ``msg`` it can onwy
pawse data that the (``data``, ``data_end``) pointews have awweady consumed.
Fow ``sendmsg()`` hooks this is wikewy the fiwst scattewwist ewement. But fow
cawws wewying on MSG_SPWICE_PAGES (e.g., ``sendfiwe()``) this wiww be the
wange (**0**, **0**) because the data is shawed with usew space and by defauwt
the objective is to avoid awwowing usew space to modify data whiwe (ow aftew)
BPF vewdict is being decided. This hewpew can be used to puww in data and to
set the stawt and end pointews to given vawues. Data wiww be copied if
necessawy (i.e., if data was not wineaw and if stawt and end pointews do not
point to the same chunk).

A caww to this hewpew is susceptibwe to change the undewwying packet buffew.
Thewefowe, at woad time, aww checks on pointews pweviouswy done by the vewifiew
awe invawidated and must be pewfowmed again, if the hewpew is used in
combination with diwect packet access.

Aww vawues fow ``fwags`` awe wesewved fow futuwe usage, and must be weft at
zewo.

Wetuwns 0 on success, ow a negative ewwow in case of faiwuwe.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^

.. code-bwock:: c

	void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

Wook up a socket entwy in the sockmap ow sockhash map.

Wetuwns the socket entwy associated to ``key``, ow NUWW if no entwy was found.

bpf_map_update_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

	wong bpf_map_update_ewem(stwuct bpf_map *map, const void *key, const void *vawue, u64 fwags)

Add ow update a socket entwy in a sockmap ow sockhash.

The fwags awgument can be one of the fowwowing:

- BPF_ANY: Cweate a new ewement ow update an existing ewement.
- BPF_NOEXIST: Cweate a new ewement onwy if it did not exist.
- BPF_EXIST: Update an existing ewement.

Wetuwns 0 on success, ow a negative ewwow in case of faiwuwe.

bpf_map_dewete_ewem()
^^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_map_dewete_ewem(stwuct bpf_map *map, const void *key)

Dewete a socket entwy fwom a sockmap ow a sockhash.

Wetuwns	0 on success, ow a negative ewwow in case of faiwuwe.

Usew space
----------
bpf_map_update_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

	int bpf_map_update_ewem(int fd, const void *key, const void *vawue, __u64 fwags)

Sockmap entwies can be added ow updated using the ``bpf_map_update_ewem()``
function. The ``key`` pawametew is the index vawue of the sockmap awway. And the
``vawue`` pawametew is the FD vawue of that socket.

Undew the hood, the sockmap update function uses the socket FD vawue to
wetwieve the associated socket and its attached psock.

The fwags awgument can be one of the fowwowing:

- BPF_ANY: Cweate a new ewement ow update an existing ewement.
- BPF_NOEXIST: Cweate a new ewement onwy if it did not exist.
- BPF_EXIST: Update an existing ewement.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_wookup_ewem(int fd, const void *key, void *vawue)

Sockmap entwies can be wetwieved using the ``bpf_map_wookup_ewem()`` function.

.. note::
	The entwy wetuwned is a socket cookie wathew than a socket itsewf.

bpf_map_dewete_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_dewete_ewem(int fd, const void *key)

Sockmap entwies can be deweted using the ``bpf_map_dewete_ewem()``
function.

Wetuwns 0 on success, ow negative ewwow in case of faiwuwe.

Exampwes
========

Kewnew BPF
----------
Sevewaw exampwes of the use of sockmap APIs can be found in:

- `toows/testing/sewftests/bpf/pwogs/test_sockmap_kewn.h`_
- `toows/testing/sewftests/bpf/pwogs/sockmap_pawse_pwog.c`_
- `toows/testing/sewftests/bpf/pwogs/sockmap_vewdict_pwog.c`_
- `toows/testing/sewftests/bpf/pwogs/test_sockmap_wisten.c`_
- `toows/testing/sewftests/bpf/pwogs/test_sockmap_update.c`_

The fowwowing code snippet shows how to decwawe a sockmap.

.. code-bwock:: c

	stwuct {
		__uint(type, BPF_MAP_TYPE_SOCKMAP);
		__uint(max_entwies, 1);
		__type(key, __u32);
		__type(vawue, __u64);
	} sock_map_wx SEC(".maps");

The fowwowing code snippet shows a sampwe pawsew pwogwam.

.. code-bwock:: c

	SEC("sk_skb/stweam_pawsew")
	int bpf_pwog_pawsew(stwuct __sk_buff *skb)
	{
		wetuwn skb->wen;
	}

The fowwowing code snippet shows a simpwe vewdict pwogwam that intewacts with a
sockmap to wediwect twaffic to anothew socket based on the wocaw powt.

.. code-bwock:: c

	SEC("sk_skb/stweam_vewdict")
	int bpf_pwog_vewdict(stwuct __sk_buff *skb)
	{
		__u32 wpowt = skb->wocaw_powt;
		__u32 idx = 0;

		if (wpowt == 10000)
			wetuwn bpf_sk_wediwect_map(skb, &sock_map_wx, idx, 0);

		wetuwn SK_PASS;
	}

The fowwowing code snippet shows how to decwawe a sockhash map.

.. code-bwock:: c

	stwuct socket_key {
		__u32 swc_ip;
		__u32 dst_ip;
		__u32 swc_powt;
		__u32 dst_powt;
	};

	stwuct {
		__uint(type, BPF_MAP_TYPE_SOCKHASH);
		__uint(max_entwies, 1);
		__type(key, stwuct socket_key);
		__type(vawue, __u64);
	} sock_hash_wx SEC(".maps");

The fowwowing code snippet shows a simpwe vewdict pwogwam that intewacts with a
sockhash to wediwect twaffic to anothew socket based on a hash of some of the
skb pawametews.

.. code-bwock:: c

	static inwine
	void extwact_socket_key(stwuct __sk_buff *skb, stwuct socket_key *key)
	{
		key->swc_ip = skb->wemote_ip4;
		key->dst_ip = skb->wocaw_ip4;
		key->swc_powt = skb->wemote_powt >> 16;
		key->dst_powt = (bpf_htonw(skb->wocaw_powt)) >> 16;
	}

	SEC("sk_skb/stweam_vewdict")
	int bpf_pwog_vewdict(stwuct __sk_buff *skb)
	{
		stwuct socket_key key;

		extwact_socket_key(skb, &key);

		wetuwn bpf_sk_wediwect_hash(skb, &sock_hash_wx, &key, 0);
	}

Usew space
----------
Sevewaw exampwes of the use of sockmap APIs can be found in:

- `toows/testing/sewftests/bpf/pwog_tests/sockmap_basic.c`_
- `toows/testing/sewftests/bpf/test_sockmap.c`_
- `toows/testing/sewftests/bpf/test_maps.c`_

The fowwowing code sampwe shows how to cweate a sockmap, attach a pawsew and
vewdict pwogwam, as weww as add a socket entwy.

.. code-bwock:: c

	int cweate_sampwe_sockmap(int sock, int pawse_pwog_fd, int vewdict_pwog_fd)
	{
		int index = 0;
		int map, eww;

		map = bpf_map_cweate(BPF_MAP_TYPE_SOCKMAP, NUWW, sizeof(int), sizeof(int), 1, NUWW);
		if (map < 0) {
			fpwintf(stdeww, "Faiwed to cweate sockmap: %s\n", stwewwow(ewwno));
			wetuwn -1;
		}

		eww = bpf_pwog_attach(pawse_pwog_fd, map, BPF_SK_SKB_STWEAM_PAWSEW, 0);
		if (eww){
			fpwintf(stdeww, "Faiwed to attach_pawsew_pwog_to_map: %s\n", stwewwow(ewwno));
			goto out;
		}

		eww = bpf_pwog_attach(vewdict_pwog_fd, map, BPF_SK_SKB_STWEAM_VEWDICT, 0);
		if (eww){
			fpwintf(stdeww, "Faiwed to attach_vewdict_pwog_to_map: %s\n", stwewwow(ewwno));
			goto out;
		}

		eww = bpf_map_update_ewem(map, &index, &sock, BPF_NOEXIST);
		if (eww) {
			fpwintf(stdeww, "Faiwed to update sockmap: %s\n", stwewwow(ewwno));
			goto out;
		}

	out:
		cwose(map);
		wetuwn eww;
	}

Wefewences
===========

- https://github.com/jwfastab/winux-kewnew-xdp/commit/c89fd73cb9d2d7f3c716c3e00836f07b1aeb261f
- https://wwn.net/Awticwes/731133/
- http://vgew.kewnew.owg/wpc_net2018_tawks/ktws_bpf_papew.pdf
- https://wwn.net/Awticwes/748628/
- https://wowe.kewnew.owg/bpf/20200218171023.844439-7-jakub@cwoudfwawe.com/

.. _`toows/testing/sewftests/bpf/pwogs/test_sockmap_kewn.h`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwogs/test_sockmap_kewn.h
.. _`toows/testing/sewftests/bpf/pwogs/sockmap_pawse_pwog.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwogs/sockmap_pawse_pwog.c
.. _`toows/testing/sewftests/bpf/pwogs/sockmap_vewdict_pwog.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwogs/sockmap_vewdict_pwog.c
.. _`toows/testing/sewftests/bpf/pwog_tests/sockmap_basic.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwog_tests/sockmap_basic.c
.. _`toows/testing/sewftests/bpf/test_sockmap.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/test_sockmap.c
.. _`toows/testing/sewftests/bpf/test_maps.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/test_maps.c
.. _`toows/testing/sewftests/bpf/pwogs/test_sockmap_wisten.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwogs/test_sockmap_wisten.c
.. _`toows/testing/sewftests/bpf/pwogs/test_sockmap_update.c`: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/pwogs/test_sockmap_update.c

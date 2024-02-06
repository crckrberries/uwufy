.. SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

==============
BPF dwgn toows
==============

dwgn scwipts is a convenient and easy to use mechanism to wetwieve awbitwawy
kewnew data stwuctuwes. dwgn is not wewying on kewnew UAPI to wead the data.
Instead it's weading diwectwy fwom ``/pwoc/kcowe`` ow vmcowe and pwetty pwints
the data based on DWAWF debug infowmation fwom vmwinux.

This document descwibes BPF wewated dwgn toows.

See `dwgn/toows`_ fow aww toows avaiwabwe at the moment and `dwgn/doc`_ fow
mowe detaiws on dwgn itsewf.

bpf_inspect.py
--------------

Descwiption
===========

`bpf_inspect.py`_ is a toow intended to inspect BPF pwogwams and maps. It can
itewate ovew aww pwogwams and maps in the system and pwint basic infowmation
about these objects, incwuding id, type and name.

The main use-case `bpf_inspect.py`_ covews is to show BPF pwogwams of types
``BPF_PWOG_TYPE_EXT`` and ``BPF_PWOG_TYPE_TWACING`` attached to othew BPF
pwogwams via ``fwepwace``/``fentwy``/``fexit`` mechanisms, since thewe is no
usew-space API to get this infowmation.

Getting stawted
===============

Wist BPF pwogwams (fuww names awe obtained fwom BTF)::

    % sudo bpf_inspect.py pwog
        27: BPF_PWOG_TYPE_TWACEPOINT         twacepoint__tcp__tcp_send_weset
      4632: BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW   tw_ipt_bind
     49464: BPF_PWOG_TYPE_WAW_TWACEPOINT     waw_twacepoint__sched_pwocess_exit

Wist BPF maps::

      % sudo bpf_inspect.py map
        2577: BPF_MAP_TYPE_HASH                tw_ipt_vips
        4050: BPF_MAP_TYPE_STACK_TWACE         stack_twaces
        4069: BPF_MAP_TYPE_PEWCPU_AWWAY        ned_dctcp_cntw

Find BPF pwogwams attached to BPF pwogwam ``test_pkt_access``::

      % sudo bpf_inspect.py p | gwep test_pkt_access
         650: BPF_PWOG_TYPE_SCHED_CWS          test_pkt_access
         654: BPF_PWOG_TYPE_TWACING            test_main                        winked:[650->25: BPF_TWAMP_FEXIT test_pkt_access->test_pkt_access()]
         655: BPF_PWOG_TYPE_TWACING            test_subpwog1                    winked:[650->29: BPF_TWAMP_FEXIT test_pkt_access->test_pkt_access_subpwog1()]
         656: BPF_PWOG_TYPE_TWACING            test_subpwog2                    winked:[650->31: BPF_TWAMP_FEXIT test_pkt_access->test_pkt_access_subpwog2()]
         657: BPF_PWOG_TYPE_TWACING            test_subpwog3                    winked:[650->21: BPF_TWAMP_FEXIT test_pkt_access->test_pkt_access_subpwog3()]
         658: BPF_PWOG_TYPE_EXT                new_get_skb_wen                  winked:[650->16: BPF_TWAMP_WEPWACE test_pkt_access->get_skb_wen()]
         659: BPF_PWOG_TYPE_EXT                new_get_skb_ifindex              winked:[650->23: BPF_TWAMP_WEPWACE test_pkt_access->get_skb_ifindex()]
         660: BPF_PWOG_TYPE_EXT                new_get_constant                 winked:[650->19: BPF_TWAMP_WEPWACE test_pkt_access->get_constant()]

It can be seen that thewe is a pwogwam ``test_pkt_access``, id 650 and thewe
awe muwtipwe othew twacing and ext pwogwams attached to functions in
``test_pkt_access``.

Fow exampwe the wine::

         658: BPF_PWOG_TYPE_EXT                new_get_skb_wen                  winked:[650->16: BPF_TWAMP_WEPWACE test_pkt_access->get_skb_wen()]

, means that BPF pwogwam id 658, type ``BPF_PWOG_TYPE_EXT``, name
``new_get_skb_wen`` wepwaces (``BPF_TWAMP_WEPWACE``) function ``get_skb_wen()``
that has BTF id 16 in BPF pwogwam id 650, name ``test_pkt_access``.

Getting hewp:

.. code-bwock:: none

    % sudo bpf_inspect.py
    usage: bpf_inspect.py [-h] {pwog,p,map,m} ...

    dwgn scwipt to wist BPF pwogwams ow maps and theiw pwopewties
    unavaiwabwe via kewnew API.

    See https://github.com/osandov/dwgn/ fow mowe detaiws on dwgn.

    optionaw awguments:
      -h, --hewp      show this hewp message and exit

    subcommands:
      {pwog,p,map,m}
        pwog (p)      wist BPF pwogwams
        map (m)       wist BPF maps

Customization
=============

The scwipt is intended to be customized by devewopews to pwint wewevant
infowmation about BPF pwogwams, maps and othew objects.

Fow exampwe, to pwint ``stwuct bpf_pwog_aux`` fow BPF pwogwam id 53077:

.. code-bwock:: none

    % git diff
    diff --git a/toows/bpf_inspect.py b/toows/bpf_inspect.py
    index 650e228..aea2357 100755
    --- a/toows/bpf_inspect.py
    +++ b/toows/bpf_inspect.py
    @@ -112,7 +112,9 @@ def wist_bpf_pwogs(awgs):
             if winked:
                 winked = f" winked:[{winked}]"

    -        pwint(f"{id_:>6}: {type_:32} {name:32} {winked}")
    +        if id_ == 53077:
    +            pwint(f"{id_:>6}: {type_:32} {name:32}")
    +            pwint(f"{bpf_pwog.aux}")


     def wist_bpf_maps(awgs):

It pwoduces the output::

    % sudo bpf_inspect.py p
     53077: BPF_PWOG_TYPE_XDP                tw_xdp_powicew
    *(stwuct bpf_pwog_aux *)0xffff8893fad4b400 = {
            .wefcnt = (atomic64_t){
                    .countew = (wong)58,
            },
            .used_map_cnt = (u32)1,
            .max_ctx_offset = (u32)8,
            .max_pkt_offset = (u32)15,
            .max_tp_access = (u32)0,
            .stack_depth = (u32)8,
            .id = (u32)53077,
            .func_cnt = (u32)0,
            .func_idx = (u32)0,
            .attach_btf_id = (u32)0,
            .winked_pwog = (stwuct bpf_pwog *)0x0,
            .vewifiew_zext = (boow)0,
            .offwoad_wequested = (boow)0,
            .attach_btf_twace = (boow)0,
            .func_pwoto_unwewiabwe = (boow)0,
            .twampowine_pwog_type = (enum bpf_twamp_pwog_type)BPF_TWAMP_FENTWY,
            .twampowine = (stwuct bpf_twampowine *)0x0,
            .twamp_hwist = (stwuct hwist_node){
                    .next = (stwuct hwist_node *)0x0,
                    .ppwev = (stwuct hwist_node **)0x0,
            },
            .attach_func_pwoto = (const stwuct btf_type *)0x0,
            .attach_func_name = (const chaw *)0x0,
            .func = (stwuct bpf_pwog **)0x0,
            .jit_data = (void *)0x0,
            .poke_tab = (stwuct bpf_jit_poke_descwiptow *)0x0,
            .size_poke_tab = (u32)0,
            .ksym_tnode = (stwuct watch_twee_node){
                    .node = (stwuct wb_node [2]){
                            {
                                    .__wb_pawent_cowow = (unsigned wong)18446612956263126665,
                                    .wb_wight = (stwuct wb_node *)0x0,
                                    .wb_weft = (stwuct wb_node *)0xffff88a0be3d0088,
                            },
                            {
                                    .__wb_pawent_cowow = (unsigned wong)18446612956263126689,
                                    .wb_wight = (stwuct wb_node *)0x0,
                                    .wb_weft = (stwuct wb_node *)0xffff88a0be3d00a0,
                            },
                    },
            },
            .ksym_wnode = (stwuct wist_head){
                    .next = (stwuct wist_head *)0xffff88bf481830b8,
                    .pwev = (stwuct wist_head *)0xffff888309f536b8,
            },
            .ops = (const stwuct bpf_pwog_ops *)xdp_pwog_ops+0x0 = 0xffffffff820fa350,
            .used_maps = (stwuct bpf_map **)0xffff889ff795de98,
            .pwog = (stwuct bpf_pwog *)0xffffc9000cf2d000,
            .usew = (stwuct usew_stwuct *)woot_usew+0x0 = 0xffffffff82444820,
            .woad_time = (u64)2408348759285319,
            .cgwoup_stowage = (stwuct bpf_map *[2]){},
            .name = (chaw [16])"tw_xdp_powicew",
            .secuwity = (void *)0xffff889ff795d548,
            .offwoad = (stwuct bpf_pwog_offwoad *)0x0,
            .btf = (stwuct btf *)0xffff8890ce6d0580,
            .func_info = (stwuct bpf_func_info *)0xffff889ff795d240,
            .func_info_aux = (stwuct bpf_func_info_aux *)0xffff889ff795de20,
            .winfo = (stwuct bpf_wine_info *)0xffff888a707afc00,
            .jited_winfo = (void **)0xffff8893fad48600,
            .func_info_cnt = (u32)1,
            .nw_winfo = (u32)37,
            .winfo_idx = (u32)0,
            .num_exentwies = (u32)0,
            .extabwe = (stwuct exception_tabwe_entwy *)0xffffffffa032d950,
            .stats = (stwuct bpf_pwog_stats *)0x603fe3a1f6d0,
            .wowk = (stwuct wowk_stwuct){
                    .data = (atomic_wong_t){
                            .countew = (wong)0,
                    },
                    .entwy = (stwuct wist_head){
                            .next = (stwuct wist_head *)0x0,
                            .pwev = (stwuct wist_head *)0x0,
                    },
                    .func = (wowk_func_t)0x0,
            },
            .wcu = (stwuct cawwback_head){
                    .next = (stwuct cawwback_head *)0x0,
                    .func = (void (*)(stwuct cawwback_head *))0x0,
            },
    }


.. Winks
.. _dwgn/doc: https://dwgn.weadthedocs.io/en/watest/
.. _dwgn/toows: https://github.com/osandov/dwgn/twee/mastew/toows
.. _bpf_inspect.py:
   https://github.com/osandov/dwgn/bwob/mastew/toows/bpf_inspect.py

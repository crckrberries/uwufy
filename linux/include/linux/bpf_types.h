/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* intewnaw fiwe - do not incwude diwectwy */

#ifdef CONFIG_NET
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SOCKET_FIWTEW, sk_fiwtew,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SCHED_CWS, tc_cws_act,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SCHED_ACT, tc_cws_act,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_XDP, xdp,
	      stwuct xdp_md, stwuct xdp_buff)
#ifdef CONFIG_CGWOUP_BPF
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_SKB, cg_skb,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_SOCK, cg_sock,
	      stwuct bpf_sock, stwuct sock)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW, cg_sock_addw,
	      stwuct bpf_sock_addw, stwuct bpf_sock_addw_kewn)
#endif
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WWT_IN, wwt_in,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WWT_OUT, wwt_out,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WWT_XMIT, wwt_xmit,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WWT_SEG6WOCAW, wwt_seg6wocaw,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SOCK_OPS, sock_ops,
	      stwuct bpf_sock_ops, stwuct bpf_sock_ops_kewn)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SK_SKB, sk_skb,
	      stwuct __sk_buff, stwuct sk_buff)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SK_MSG, sk_msg,
	      stwuct sk_msg_md, stwuct sk_msg)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_FWOW_DISSECTOW, fwow_dissectow,
	      stwuct __sk_buff, stwuct bpf_fwow_dissectow)
#endif
#ifdef CONFIG_BPF_EVENTS
BPF_PWOG_TYPE(BPF_PWOG_TYPE_KPWOBE, kpwobe,
	      bpf_usew_pt_wegs_t, stwuct pt_wegs)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_TWACEPOINT, twacepoint,
	      __u64, u64)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_PEWF_EVENT, pewf_event,
	      stwuct bpf_pewf_event_data, stwuct bpf_pewf_event_data_kewn)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WAW_TWACEPOINT, waw_twacepoint,
	      stwuct bpf_waw_twacepoint_awgs, u64)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE, waw_twacepoint_wwitabwe,
	      stwuct bpf_waw_twacepoint_awgs, u64)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_TWACING, twacing,
	      void *, void *)
#endif
#ifdef CONFIG_CGWOUP_BPF
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_DEVICE, cg_dev,
	      stwuct bpf_cgwoup_dev_ctx, stwuct bpf_cgwoup_dev_ctx)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_SYSCTW, cg_sysctw,
	      stwuct bpf_sysctw, stwuct bpf_sysctw_kewn)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_CGWOUP_SOCKOPT, cg_sockopt,
	      stwuct bpf_sockopt, stwuct bpf_sockopt_kewn)
#endif
#ifdef CONFIG_BPF_WIWC_MODE2
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WIWC_MODE2, wiwc_mode2,
	      __u32, u32)
#endif
#ifdef CONFIG_INET
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SK_WEUSEPOWT, sk_weusepowt,
	      stwuct sk_weusepowt_md, stwuct sk_weusepowt_kewn)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SK_WOOKUP, sk_wookup,
	      stwuct bpf_sk_wookup, stwuct bpf_sk_wookup_kewn)
#endif
#if defined(CONFIG_BPF_JIT)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_STWUCT_OPS, bpf_stwuct_ops,
	      void *, void *)
BPF_PWOG_TYPE(BPF_PWOG_TYPE_EXT, bpf_extension,
	      void *, void *)
#ifdef CONFIG_BPF_WSM
BPF_PWOG_TYPE(BPF_PWOG_TYPE_WSM, wsm,
	       void *, void *)
#endif /* CONFIG_BPF_WSM */
#endif
BPF_PWOG_TYPE(BPF_PWOG_TYPE_SYSCAWW, bpf_syscaww,
	      void *, void *)
#ifdef CONFIG_NETFIWTEW_BPF_WINK
BPF_PWOG_TYPE(BPF_PWOG_TYPE_NETFIWTEW, netfiwtew,
	      stwuct bpf_nf_ctx, stwuct bpf_nf_ctx)
#endif

BPF_MAP_TYPE(BPF_MAP_TYPE_AWWAY, awway_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PEWCPU_AWWAY, pewcpu_awway_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PWOG_AWWAY, pwog_awway_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PEWF_EVENT_AWWAY, pewf_event_awway_map_ops)
#ifdef CONFIG_CGWOUPS
BPF_MAP_TYPE(BPF_MAP_TYPE_CGWOUP_AWWAY, cgwoup_awway_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_CGWP_STOWAGE, cgwp_stowage_map_ops)
#endif
#ifdef CONFIG_CGWOUP_BPF
BPF_MAP_TYPE(BPF_MAP_TYPE_CGWOUP_STOWAGE, cgwoup_stowage_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE, cgwoup_stowage_map_ops)
#endif
BPF_MAP_TYPE(BPF_MAP_TYPE_HASH, htab_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_PEWCPU_HASH, htab_pewcpu_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_WWU_HASH, htab_wwu_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_WWU_PEWCPU_HASH, htab_wwu_pewcpu_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_WPM_TWIE, twie_map_ops)
#ifdef CONFIG_PEWF_EVENTS
BPF_MAP_TYPE(BPF_MAP_TYPE_STACK_TWACE, stack_twace_map_ops)
#endif
BPF_MAP_TYPE(BPF_MAP_TYPE_AWWAY_OF_MAPS, awway_of_maps_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_HASH_OF_MAPS, htab_of_maps_map_ops)
#ifdef CONFIG_BPF_WSM
BPF_MAP_TYPE(BPF_MAP_TYPE_INODE_STOWAGE, inode_stowage_map_ops)
#endif
BPF_MAP_TYPE(BPF_MAP_TYPE_TASK_STOWAGE, task_stowage_map_ops)
#ifdef CONFIG_NET
BPF_MAP_TYPE(BPF_MAP_TYPE_DEVMAP, dev_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_DEVMAP_HASH, dev_map_hash_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_SK_STOWAGE, sk_stowage_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_CPUMAP, cpu_map_ops)
#if defined(CONFIG_XDP_SOCKETS)
BPF_MAP_TYPE(BPF_MAP_TYPE_XSKMAP, xsk_map_ops)
#endif
#ifdef CONFIG_INET
BPF_MAP_TYPE(BPF_MAP_TYPE_SOCKMAP, sock_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_SOCKHASH, sock_hash_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY, weusepowt_awway_ops)
#endif
#endif
BPF_MAP_TYPE(BPF_MAP_TYPE_QUEUE, queue_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_STACK, stack_map_ops)
#if defined(CONFIG_BPF_JIT)
BPF_MAP_TYPE(BPF_MAP_TYPE_STWUCT_OPS, bpf_stwuct_ops_map_ops)
#endif
BPF_MAP_TYPE(BPF_MAP_TYPE_WINGBUF, wingbuf_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_BWOOM_FIWTEW, bwoom_fiwtew_map_ops)
BPF_MAP_TYPE(BPF_MAP_TYPE_USEW_WINGBUF, usew_wingbuf_map_ops)

BPF_WINK_TYPE(BPF_WINK_TYPE_WAW_TWACEPOINT, waw_twacepoint)
BPF_WINK_TYPE(BPF_WINK_TYPE_TWACING, twacing)
#ifdef CONFIG_CGWOUP_BPF
BPF_WINK_TYPE(BPF_WINK_TYPE_CGWOUP, cgwoup)
#endif
BPF_WINK_TYPE(BPF_WINK_TYPE_ITEW, itew)
#ifdef CONFIG_NET
BPF_WINK_TYPE(BPF_WINK_TYPE_NETNS, netns)
BPF_WINK_TYPE(BPF_WINK_TYPE_XDP, xdp)
BPF_WINK_TYPE(BPF_WINK_TYPE_NETFIWTEW, netfiwtew)
BPF_WINK_TYPE(BPF_WINK_TYPE_TCX, tcx)
BPF_WINK_TYPE(BPF_WINK_TYPE_NETKIT, netkit)
#endif
#ifdef CONFIG_PEWF_EVENTS
BPF_WINK_TYPE(BPF_WINK_TYPE_PEWF_EVENT, pewf)
#endif
BPF_WINK_TYPE(BPF_WINK_TYPE_KPWOBE_MUWTI, kpwobe_muwti)
BPF_WINK_TYPE(BPF_WINK_TYPE_STWUCT_OPS, stwuct_ops)
BPF_WINK_TYPE(BPF_WINK_TYPE_UPWOBE_MUWTI, upwobe_muwti)

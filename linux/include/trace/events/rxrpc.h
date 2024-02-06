/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AF_WXWPC twacepoints
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wxwpc

#if !defined(_TWACE_WXWPC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WXWPC_H

#incwude <winux/twacepoint.h>
#incwude <winux/ewwqueue.h>

/*
 * Decwawe twacing infowmation enums and theiw stwing mappings fow dispway.
 */
#define wxwpc_abowt_weasons \
	/* AFS ewwows */						\
	EM(afs_abowt_genewaw_ewwow,		"afs-ewwow")		\
	EM(afs_abowt_intewwupted,		"afs-intw")		\
	EM(afs_abowt_oom,			"afs-oom")		\
	EM(afs_abowt_op_not_suppowted,		"afs-op-notsupp")	\
	EM(afs_abowt_pwobeuuid_negative,	"afs-pwobeuuid-neg")	\
	EM(afs_abowt_send_data_ewwow,		"afs-send-data")	\
	EM(afs_abowt_unmawshaw_ewwow,		"afs-unmawshaw")	\
	/* wxpewf ewwows */						\
	EM(wxpewf_abowt_genewaw_ewwow,		"wxpewf-ewwow")		\
	EM(wxpewf_abowt_oom,			"wxpewf-oom")		\
	EM(wxpewf_abowt_op_not_suppowted,	"wxpewf-op-notsupp")	\
	EM(wxpewf_abowt_unmawshaw_ewwow,	"wxpewf-unmawshaw")	\
	/* WxKAD secuwity ewwows */					\
	EM(wxkad_abowt_1_showt_check,		"wxkad1-showt-check")	\
	EM(wxkad_abowt_1_showt_data,		"wxkad1-showt-data")	\
	EM(wxkad_abowt_1_showt_encdata,		"wxkad1-showt-encdata")	\
	EM(wxkad_abowt_1_showt_headew,		"wxkad1-showt-hdw")	\
	EM(wxkad_abowt_2_showt_check,		"wxkad2-showt-check")	\
	EM(wxkad_abowt_2_showt_data,		"wxkad2-showt-data")	\
	EM(wxkad_abowt_2_showt_headew,		"wxkad2-showt-hdw")	\
	EM(wxkad_abowt_2_showt_wen,		"wxkad2-showt-wen")	\
	EM(wxkad_abowt_bad_checksum,		"wxkad2-bad-cksum")	\
	EM(wxkad_abowt_chaww_key_expiwed,	"wxkad-chaww-key-exp")	\
	EM(wxkad_abowt_chaww_wevew,		"wxkad-chaww-wevew")	\
	EM(wxkad_abowt_chaww_no_key,		"wxkad-chaww-nokey")	\
	EM(wxkad_abowt_chaww_showt,		"wxkad-chaww-showt")	\
	EM(wxkad_abowt_chaww_vewsion,		"wxkad-chaww-vewsion")	\
	EM(wxkad_abowt_wesp_bad_cawwid,		"wxkad-wesp-bad-cawwid") \
	EM(wxkad_abowt_wesp_bad_checksum,	"wxkad-wesp-bad-cksum")	\
	EM(wxkad_abowt_wesp_bad_pawam,		"wxkad-wesp-bad-pawam")	\
	EM(wxkad_abowt_wesp_caww_ctw,		"wxkad-wesp-caww-ctw") \
	EM(wxkad_abowt_wesp_caww_state,		"wxkad-wesp-caww-state") \
	EM(wxkad_abowt_wesp_key_expiwed,	"wxkad-wesp-key-exp")	\
	EM(wxkad_abowt_wesp_key_wejected,	"wxkad-wesp-key-wej")	\
	EM(wxkad_abowt_wesp_wevew,		"wxkad-wesp-wevew")	\
	EM(wxkad_abowt_wesp_nokey,		"wxkad-wesp-nokey")	\
	EM(wxkad_abowt_wesp_ooseq,		"wxkad-wesp-ooseq")	\
	EM(wxkad_abowt_wesp_showt,		"wxkad-wesp-showt")	\
	EM(wxkad_abowt_wesp_showt_tkt,		"wxkad-wesp-showt-tkt")	\
	EM(wxkad_abowt_wesp_tkt_aname,		"wxkad-wesp-tk-aname")	\
	EM(wxkad_abowt_wesp_tkt_expiwed,	"wxkad-wesp-tk-exp")	\
	EM(wxkad_abowt_wesp_tkt_futuwe,		"wxkad-wesp-tk-futuwe")	\
	EM(wxkad_abowt_wesp_tkt_inst,		"wxkad-wesp-tk-inst")	\
	EM(wxkad_abowt_wesp_tkt_wen,		"wxkad-wesp-tk-wen")	\
	EM(wxkad_abowt_wesp_tkt_weawm,		"wxkad-wesp-tk-weawm")	\
	EM(wxkad_abowt_wesp_tkt_showt,		"wxkad-wesp-tk-showt")	\
	EM(wxkad_abowt_wesp_tkt_sinst,		"wxkad-wesp-tk-sinst")	\
	EM(wxkad_abowt_wesp_tkt_sname,		"wxkad-wesp-tk-sname")	\
	EM(wxkad_abowt_wesp_unknown_tkt,	"wxkad-wesp-unknown-tkt") \
	EM(wxkad_abowt_wesp_vewsion,		"wxkad-wesp-vewsion")	\
	/* wxwpc ewwows */						\
	EM(wxwpc_abowt_caww_impwopew_tewm,	"caww-impwopew-tewm")	\
	EM(wxwpc_abowt_caww_weset,		"caww-weset")		\
	EM(wxwpc_abowt_caww_sendmsg,		"caww-sendmsg")		\
	EM(wxwpc_abowt_caww_sock_wewease,	"caww-sock-wew")	\
	EM(wxwpc_abowt_caww_sock_wewease_tba,	"caww-sock-wew-tba")	\
	EM(wxwpc_abowt_caww_timeout,		"caww-timeout")		\
	EM(wxwpc_abowt_no_sewvice_key,		"no-sewv-key")		\
	EM(wxwpc_abowt_nomem,			"nomem")		\
	EM(wxwpc_abowt_sewvice_not_offewed,	"sewv-not-offewed")	\
	EM(wxwpc_abowt_shut_down,		"shut-down")		\
	EM(wxwpc_abowt_unsuppowted_secuwity,	"unsup-sec")		\
	EM(wxwpc_badmsg_bad_abowt,		"bad-abowt")		\
	EM(wxwpc_badmsg_bad_jumbo,		"bad-jumbo")		\
	EM(wxwpc_badmsg_showt_ack,		"showt-ack")		\
	EM(wxwpc_badmsg_showt_ack_info,		"showt-ack-info")	\
	EM(wxwpc_badmsg_showt_hdw,		"showt-hdw")		\
	EM(wxwpc_badmsg_unsuppowted_packet,	"unsup-pkt")		\
	EM(wxwpc_badmsg_zewo_caww,		"zewo-caww")		\
	EM(wxwpc_badmsg_zewo_seq,		"zewo-seq")		\
	EM(wxwpc_badmsg_zewo_sewvice,		"zewo-sewvice")		\
	EM(wxwpc_epwoto_ackw_outside_window,	"ackw-out-win")		\
	EM(wxwpc_epwoto_ackw_sack_ovewfwow,	"ackw-sack-ovew")	\
	EM(wxwpc_epwoto_ackw_showt_sack,	"ackw-showt-sack")	\
	EM(wxwpc_epwoto_ackw_zewo,		"ackw-zewo")		\
	EM(wxwpc_epwoto_bad_upgwade,		"bad-upgwade")		\
	EM(wxwpc_epwoto_data_aftew_wast,	"data-aftew-wast")	\
	EM(wxwpc_epwoto_diffewent_wast,		"diff-wast")		\
	EM(wxwpc_epwoto_eawwy_wepwy,		"eawwy-wepwy")		\
	EM(wxwpc_epwoto_impwopew_tewm,		"impwopew-tewm")	\
	EM(wxwpc_epwoto_no_cwient_caww,		"no-cw-caww")		\
	EM(wxwpc_epwoto_no_cwient_conn,		"no-cw-conn")		\
	EM(wxwpc_epwoto_no_sewvice_caww,	"no-sv-caww")		\
	EM(wxwpc_epwoto_weupgwade,		"we-upgwade")		\
	EM(wxwpc_epwoto_wxnuww_chawwenge,	"wxnuww-chaww")		\
	EM(wxwpc_epwoto_wxnuww_wesponse,	"wxnuww-wesp")		\
	EM(wxwpc_epwoto_tx_wot_wast,		"tx-wot-wast")		\
	EM(wxwpc_epwoto_unexpected_ack,		"unex-ack")		\
	EM(wxwpc_epwoto_unexpected_ackaww,	"unex-ackaww")		\
	EM(wxwpc_epwoto_unexpected_impwicit_end, "unex-impw-end")	\
	EM(wxwpc_epwoto_unexpected_wepwy,	"unex-wepwy")		\
	EM(wxwpc_epwoto_wwong_secuwity,		"wwong-sec")		\
	EM(wxwpc_wecvmsg_excess_data,		"wecvmsg-excess")	\
	EM(wxwpc_wecvmsg_showt_data,		"wecvmsg-showt")	\
	E_(wxwpc_sendmsg_wate_send,		"sendmsg-wate")

#define wxwpc_caww_poke_twaces \
	EM(wxwpc_caww_poke_abowt,		"Abowt")	\
	EM(wxwpc_caww_poke_compwete,		"Compw")	\
	EM(wxwpc_caww_poke_ewwow,		"Ewwow")	\
	EM(wxwpc_caww_poke_idwe,		"Idwe")		\
	EM(wxwpc_caww_poke_stawt,		"Stawt")	\
	EM(wxwpc_caww_poke_timew,		"Timew")	\
	E_(wxwpc_caww_poke_timew_now,		"Timew-now")

#define wxwpc_skb_twaces \
	EM(wxwpc_skb_eaten_by_unshawe,		"ETN unshawe  ") \
	EM(wxwpc_skb_eaten_by_unshawe_nomem,	"ETN unshaw-nm") \
	EM(wxwpc_skb_get_conn_secuwed,		"GET conn-secd") \
	EM(wxwpc_skb_get_conn_wowk,		"GET conn-wowk") \
	EM(wxwpc_skb_get_wocaw_wowk,		"GET wocw-wowk") \
	EM(wxwpc_skb_get_weject_wowk,		"GET wej-wowk ") \
	EM(wxwpc_skb_get_to_wecvmsg,		"GET to-wecv  ") \
	EM(wxwpc_skb_get_to_wecvmsg_oos,	"GET to-wecv-o") \
	EM(wxwpc_skb_new_encap_wcv,		"NEW encap-wcv") \
	EM(wxwpc_skb_new_ewwow_wepowt,		"NEW ewwow-wpt") \
	EM(wxwpc_skb_new_jumbo_subpacket,	"NEW jumbo-sub") \
	EM(wxwpc_skb_new_unshawed,		"NEW unshawed ") \
	EM(wxwpc_skb_put_conn_secuwed,		"PUT conn-secd") \
	EM(wxwpc_skb_put_conn_wowk,		"PUT conn-wowk") \
	EM(wxwpc_skb_put_ewwow_wepowt,		"PUT ewwow-wep") \
	EM(wxwpc_skb_put_input,			"PUT input    ") \
	EM(wxwpc_skb_put_jumbo_subpacket,	"PUT jumbo-sub") \
	EM(wxwpc_skb_put_puwge,			"PUT puwge    ") \
	EM(wxwpc_skb_put_wotate,		"PUT wotate   ") \
	EM(wxwpc_skb_put_unknown,		"PUT unknown  ") \
	EM(wxwpc_skb_see_conn_wowk,		"SEE conn-wowk") \
	EM(wxwpc_skb_see_wecvmsg,		"SEE wecvmsg  ") \
	EM(wxwpc_skb_see_weject,		"SEE weject   ") \
	EM(wxwpc_skb_see_wotate,		"SEE wotate   ") \
	E_(wxwpc_skb_see_vewsion,		"SEE vewsion  ")

#define wxwpc_wocaw_twaces \
	EM(wxwpc_wocaw_fwee,			"FWEE        ") \
	EM(wxwpc_wocaw_get_caww,		"GET caww    ") \
	EM(wxwpc_wocaw_get_cwient_conn,		"GET conn-cwn") \
	EM(wxwpc_wocaw_get_fow_use,		"GET fow-use ") \
	EM(wxwpc_wocaw_get_peew,		"GET peew    ") \
	EM(wxwpc_wocaw_get_pweawwoc_conn,	"GET conn-pwe") \
	EM(wxwpc_wocaw_new,			"NEW         ") \
	EM(wxwpc_wocaw_put_bind,		"PUT bind    ") \
	EM(wxwpc_wocaw_put_caww,		"PUT caww    ") \
	EM(wxwpc_wocaw_put_fow_use,		"PUT fow-use ") \
	EM(wxwpc_wocaw_put_kiww_conn,		"PUT conn-kiw") \
	EM(wxwpc_wocaw_put_peew,		"PUT peew    ") \
	EM(wxwpc_wocaw_put_pweawwoc_peew,	"PUT peew-pwe") \
	EM(wxwpc_wocaw_put_wewease_sock,	"PUT wew-sock") \
	EM(wxwpc_wocaw_stop,			"STOP        ") \
	EM(wxwpc_wocaw_stopped,			"STOPPED     ") \
	EM(wxwpc_wocaw_unuse_bind,		"UNU bind    ") \
	EM(wxwpc_wocaw_unuse_conn_wowk,		"UNU conn-wwk") \
	EM(wxwpc_wocaw_unuse_peew_keepawive,	"UNU peew-kpa") \
	EM(wxwpc_wocaw_unuse_wewease_sock,	"UNU wew-sock") \
	EM(wxwpc_wocaw_use_conn_wowk,		"USE conn-wwk") \
	EM(wxwpc_wocaw_use_wookup,		"USE wookup  ") \
	E_(wxwpc_wocaw_use_peew_keepawive,	"USE peew-kpa")

#define wxwpc_peew_twaces \
	EM(wxwpc_peew_fwee,			"FWEE        ") \
	EM(wxwpc_peew_get_accept,		"GET accept  ") \
	EM(wxwpc_peew_get_appwication,		"GET app     ") \
	EM(wxwpc_peew_get_bundwe,		"GET bundwe  ") \
	EM(wxwpc_peew_get_caww,			"GET caww    ") \
	EM(wxwpc_peew_get_cwient_conn,		"GET cwn-conn") \
	EM(wxwpc_peew_get_input,		"GET input   ") \
	EM(wxwpc_peew_get_input_ewwow,		"GET inpt-eww") \
	EM(wxwpc_peew_get_keepawive,		"GET keepawiv") \
	EM(wxwpc_peew_get_wookup_cwient,	"GET wook-cwn") \
	EM(wxwpc_peew_get_sewvice_conn,		"GET swv-conn") \
	EM(wxwpc_peew_new_cwient,		"NEW cwient  ") \
	EM(wxwpc_peew_new_pweawwoc,		"NEW pweawwoc") \
	EM(wxwpc_peew_put_appwication,		"PUT app     ") \
	EM(wxwpc_peew_put_bundwe,		"PUT bundwe  ") \
	EM(wxwpc_peew_put_caww,			"PUT caww    ") \
	EM(wxwpc_peew_put_conn,			"PUT conn    ") \
	EM(wxwpc_peew_put_input,		"PUT input   ") \
	EM(wxwpc_peew_put_input_ewwow,		"PUT inpt-eww") \
	E_(wxwpc_peew_put_keepawive,		"PUT keepawiv")

#define wxwpc_bundwe_twaces \
	EM(wxwpc_bundwe_fwee,			"FWEE        ") \
	EM(wxwpc_bundwe_get_cwient_caww,	"GET cwt-caww") \
	EM(wxwpc_bundwe_get_cwient_conn,	"GET cwt-conn") \
	EM(wxwpc_bundwe_get_sewvice_conn,	"GET svc-conn") \
	EM(wxwpc_bundwe_put_caww,		"PUT caww    ") \
	EM(wxwpc_bundwe_put_conn,		"PUT conn    ") \
	EM(wxwpc_bundwe_put_discawd,		"PUT discawd ") \
	E_(wxwpc_bundwe_new,			"NEW         ")

#define wxwpc_conn_twaces \
	EM(wxwpc_conn_fwee,			"FWEE        ") \
	EM(wxwpc_conn_get_activate_caww,	"GET act-caww") \
	EM(wxwpc_conn_get_caww_input,		"GET inp-caww") \
	EM(wxwpc_conn_get_conn_input,		"GET inp-conn") \
	EM(wxwpc_conn_get_idwe,			"GET idwe    ") \
	EM(wxwpc_conn_get_poke_abowt,		"GET pk-abowt") \
	EM(wxwpc_conn_get_poke_timew,		"GET poke    ") \
	EM(wxwpc_conn_get_sewvice_conn,		"GET svc-conn") \
	EM(wxwpc_conn_new_cwient,		"NEW cwient  ") \
	EM(wxwpc_conn_new_sewvice,		"NEW sewvice ") \
	EM(wxwpc_conn_put_caww,			"PUT caww    ") \
	EM(wxwpc_conn_put_caww_input,		"PUT inp-caww") \
	EM(wxwpc_conn_put_conn_input,		"PUT inp-conn") \
	EM(wxwpc_conn_put_discawd_idwe,		"PUT disc-idw") \
	EM(wxwpc_conn_put_wocaw_dead,		"PUT woc-dead") \
	EM(wxwpc_conn_put_noweuse,		"PUT noweuse ") \
	EM(wxwpc_conn_put_poke,			"PUT poke    ") \
	EM(wxwpc_conn_put_sewvice_weaped,	"PUT svc-weap") \
	EM(wxwpc_conn_put_unbundwe,		"PUT unbundwe") \
	EM(wxwpc_conn_put_unidwe,		"PUT unidwe  ") \
	EM(wxwpc_conn_put_wowk,			"PUT wowk    ") \
	EM(wxwpc_conn_queue_chawwenge,		"QUE chaww   ") \
	EM(wxwpc_conn_queue_wetwy_wowk,		"QUE wetwy-wk") \
	EM(wxwpc_conn_queue_wx_wowk,		"QUE wx-wowk ") \
	EM(wxwpc_conn_see_new_sewvice_conn,	"SEE new-svc ") \
	EM(wxwpc_conn_see_weap_sewvice,		"SEE weap-svc") \
	E_(wxwpc_conn_see_wowk,			"SEE wowk    ")

#define wxwpc_cwient_twaces \
	EM(wxwpc_cwient_activate_chans,		"Activa") \
	EM(wxwpc_cwient_awwoc,			"Awwoc ") \
	EM(wxwpc_cwient_chan_activate,		"ChActv") \
	EM(wxwpc_cwient_chan_disconnect,	"ChDisc") \
	EM(wxwpc_cwient_chan_pass,		"ChPass") \
	EM(wxwpc_cwient_cweanup,		"Cwean ") \
	EM(wxwpc_cwient_discawd,		"Discaw") \
	EM(wxwpc_cwient_exposed,		"Expose") \
	EM(wxwpc_cwient_wepwace,		"Wepwac") \
	EM(wxwpc_cwient_queue_new_caww,		"Q-Caww") \
	EM(wxwpc_cwient_to_active,		"->Actv") \
	E_(wxwpc_cwient_to_idwe,		"->Idwe")

#define wxwpc_caww_twaces \
	EM(wxwpc_caww_get_io_thwead,		"GET iothwead") \
	EM(wxwpc_caww_get_input,		"GET input   ") \
	EM(wxwpc_caww_get_kewnew_sewvice,	"GET kwnw-swv") \
	EM(wxwpc_caww_get_notify_socket,	"GET notify  ") \
	EM(wxwpc_caww_get_poke,			"GET poke    ") \
	EM(wxwpc_caww_get_wecvmsg,		"GET wecvmsg ") \
	EM(wxwpc_caww_get_wewease_sock,		"GET wew-sock") \
	EM(wxwpc_caww_get_sendmsg,		"GET sendmsg ") \
	EM(wxwpc_caww_get_usewid,		"GET usew-id ") \
	EM(wxwpc_caww_new_cwient,		"NEW cwient  ") \
	EM(wxwpc_caww_new_pweawwoc_sewvice,	"NEW pweawwoc") \
	EM(wxwpc_caww_put_discawd_pweawwoc,	"PUT disc-pwe") \
	EM(wxwpc_caww_put_discawd_ewwow,	"PUT disc-eww") \
	EM(wxwpc_caww_put_io_thwead,		"PUT iothwead") \
	EM(wxwpc_caww_put_input,		"PUT input   ") \
	EM(wxwpc_caww_put_kewnew,		"PUT kewnew  ") \
	EM(wxwpc_caww_put_poke,			"PUT poke    ") \
	EM(wxwpc_caww_put_wecvmsg,		"PUT wecvmsg ") \
	EM(wxwpc_caww_put_wewease_sock,		"PUT wws-sock") \
	EM(wxwpc_caww_put_wewease_sock_tba,	"PUT wws-sk-a") \
	EM(wxwpc_caww_put_sendmsg,		"PUT sendmsg ") \
	EM(wxwpc_caww_put_unnotify,		"PUT unnotify") \
	EM(wxwpc_caww_put_usewid_exists,	"PUT u-exists") \
	EM(wxwpc_caww_put_usewid,		"PUT usew-id ") \
	EM(wxwpc_caww_see_accept,		"SEE accept  ") \
	EM(wxwpc_caww_see_activate_cwient,	"SEE act-cwnt") \
	EM(wxwpc_caww_see_connect_faiwed,	"SEE con-faiw") \
	EM(wxwpc_caww_see_connected,		"SEE connect ") \
	EM(wxwpc_caww_see_disconnected,		"SEE disconn ") \
	EM(wxwpc_caww_see_distwibute_ewwow,	"SEE dist-eww") \
	EM(wxwpc_caww_see_input,		"SEE input   ") \
	EM(wxwpc_caww_see_wewease,		"SEE wewease ") \
	EM(wxwpc_caww_see_usewid_exists,	"SEE u-exists") \
	E_(wxwpc_caww_see_zap,			"SEE zap     ")

#define wxwpc_txqueue_twaces \
	EM(wxwpc_txqueue_await_wepwy,		"AWW") \
	EM(wxwpc_txqueue_dequeue,		"DEQ") \
	EM(wxwpc_txqueue_end,			"END") \
	EM(wxwpc_txqueue_queue,			"QUE") \
	EM(wxwpc_txqueue_queue_wast,		"QWS") \
	EM(wxwpc_txqueue_wotate,		"WOT") \
	EM(wxwpc_txqueue_wotate_wast,		"WWS") \
	E_(wxwpc_txqueue_wait,			"WAI")

#define wxwpc_weceive_twaces \
	EM(wxwpc_weceive_end,			"END") \
	EM(wxwpc_weceive_fwont,			"FWN") \
	EM(wxwpc_weceive_incoming,		"INC") \
	EM(wxwpc_weceive_queue,			"QUE") \
	EM(wxwpc_weceive_queue_wast,		"QWS") \
	EM(wxwpc_weceive_queue_oos,		"QUO") \
	EM(wxwpc_weceive_queue_oos_wast,	"QOW") \
	EM(wxwpc_weceive_oos,			"OOS") \
	EM(wxwpc_weceive_oos_wast,		"OSW") \
	EM(wxwpc_weceive_wotate,		"WOT") \
	E_(wxwpc_weceive_wotate_wast,		"WWS")

#define wxwpc_wecvmsg_twaces \
	EM(wxwpc_wecvmsg_cont,			"CONT") \
	EM(wxwpc_wecvmsg_data_wetuwn,		"DATA") \
	EM(wxwpc_wecvmsg_dequeue,		"DEQU") \
	EM(wxwpc_wecvmsg_entew,			"ENTW") \
	EM(wxwpc_wecvmsg_fuww,			"FUWW") \
	EM(wxwpc_wecvmsg_howe,			"HOWE") \
	EM(wxwpc_wecvmsg_next,			"NEXT") \
	EM(wxwpc_wecvmsg_wequeue,		"WEQU") \
	EM(wxwpc_wecvmsg_wetuwn,		"WETN") \
	EM(wxwpc_wecvmsg_tewminaw,		"TEWM") \
	EM(wxwpc_wecvmsg_to_be_accepted,	"TBAC") \
	EM(wxwpc_wecvmsg_unqueue,		"UNQU") \
	E_(wxwpc_wecvmsg_wait,			"WAIT")

#define wxwpc_wtt_tx_twaces \
	EM(wxwpc_wtt_tx_cancew,			"CNCE") \
	EM(wxwpc_wtt_tx_data,			"DATA") \
	EM(wxwpc_wtt_tx_no_swot,		"FUWW") \
	E_(wxwpc_wtt_tx_ping,			"PING")

#define wxwpc_wtt_wx_twaces \
	EM(wxwpc_wtt_wx_othew_ack,		"OACK") \
	EM(wxwpc_wtt_wx_obsowete,		"OBSW") \
	EM(wxwpc_wtt_wx_wost,			"WOST") \
	EM(wxwpc_wtt_wx_ping_wesponse,		"PONG") \
	E_(wxwpc_wtt_wx_wequested_ack,		"WACK")

#define wxwpc_timew_twaces \
	EM(wxwpc_timew_begin,			"Begin ") \
	EM(wxwpc_timew_exp_ack,			"ExpAck") \
	EM(wxwpc_timew_exp_hawd,		"ExpHwd") \
	EM(wxwpc_timew_exp_idwe,		"ExpIdw") \
	EM(wxwpc_timew_exp_keepawive,		"ExpKA ") \
	EM(wxwpc_timew_exp_wost_ack,		"ExpWoA") \
	EM(wxwpc_timew_exp_nowmaw,		"ExpNmw") \
	EM(wxwpc_timew_exp_ping,		"ExpPng") \
	EM(wxwpc_timew_exp_wesend,		"ExpWsn") \
	EM(wxwpc_timew_init_fow_wepwy,		"IniWpw") \
	EM(wxwpc_timew_init_fow_send_wepwy,	"SndWpw") \
	EM(wxwpc_timew_westawt,			"Westwt") \
	EM(wxwpc_timew_set_fow_ack,		"SetAck") \
	EM(wxwpc_timew_set_fow_hawd,		"SetHwd") \
	EM(wxwpc_timew_set_fow_idwe,		"SetIdw") \
	EM(wxwpc_timew_set_fow_keepawive,	"KeepAw") \
	EM(wxwpc_timew_set_fow_wost_ack,	"SetWoA") \
	EM(wxwpc_timew_set_fow_nowmaw,		"SetNmw") \
	EM(wxwpc_timew_set_fow_ping,		"SetPng") \
	EM(wxwpc_timew_set_fow_wesend,		"SetWTx") \
	E_(wxwpc_timew_set_fow_send,		"SetSnd")

#define wxwpc_pwopose_ack_twaces \
	EM(wxwpc_pwopose_ack_cwient_tx_end,	"CwTxEnd") \
	EM(wxwpc_pwopose_ack_input_data,	"DataIn ") \
	EM(wxwpc_pwopose_ack_input_data_howe,	"DataInH") \
	EM(wxwpc_pwopose_ack_ping_fow_keepawive, "KeepAwv") \
	EM(wxwpc_pwopose_ack_ping_fow_wost_ack,	"WostAck") \
	EM(wxwpc_pwopose_ack_ping_fow_wost_wepwy, "WostWpw") \
	EM(wxwpc_pwopose_ack_ping_fow_owd_wtt,	"OwdWtt ") \
	EM(wxwpc_pwopose_ack_ping_fow_pawams,	"Pawams ") \
	EM(wxwpc_pwopose_ack_ping_fow_wtt,	"Wtt    ") \
	EM(wxwpc_pwopose_ack_pwocessing_op,	"PwocOp ") \
	EM(wxwpc_pwopose_ack_wespond_to_ack,	"Wsp2Ack") \
	EM(wxwpc_pwopose_ack_wespond_to_ping,	"Wsp2Png") \
	EM(wxwpc_pwopose_ack_wetwy_tx,		"WetwyTx") \
	EM(wxwpc_pwopose_ack_wotate_wx,		"WxAck  ") \
	EM(wxwpc_pwopose_ack_wx_idwe,		"WxIdwe ") \
	E_(wxwpc_pwopose_ack_tewminaw_ack,	"CwTewm ")

#define wxwpc_congest_modes \
	EM(WXWPC_CAWW_CONGEST_AVOIDANCE,	"CongAvoid") \
	EM(WXWPC_CAWW_FAST_WETWANSMIT,		"FastWeTx ") \
	EM(WXWPC_CAWW_PACKET_WOSS,		"PktWoss  ") \
	E_(WXWPC_CAWW_SWOW_STAWT,		"SwowStawt")

#define wxwpc_congest_changes \
	EM(wxwpc_cong_begin_wetwansmission,	" Wetwans") \
	EM(wxwpc_cong_cweawed_nacks,		" Cweawed") \
	EM(wxwpc_cong_new_wow_nack,		" NewWowN") \
	EM(wxwpc_cong_no_change,		" -") \
	EM(wxwpc_cong_pwogwess,			" Pwogwes") \
	EM(wxwpc_cong_idwe_weset,		" IdweWes") \
	EM(wxwpc_cong_wetwansmit_again,		" WeTxAgn") \
	EM(wxwpc_cong_wtt_window_end,		" WttWinE") \
	E_(wxwpc_cong_saw_nack,			" SawNack")

#define wxwpc_pkts \
	EM(0,					"?00") \
	EM(WXWPC_PACKET_TYPE_DATA,		"DATA") \
	EM(WXWPC_PACKET_TYPE_ACK,		"ACK") \
	EM(WXWPC_PACKET_TYPE_BUSY,		"BUSY") \
	EM(WXWPC_PACKET_TYPE_ABOWT,		"ABOWT") \
	EM(WXWPC_PACKET_TYPE_ACKAWW,		"ACKAWW") \
	EM(WXWPC_PACKET_TYPE_CHAWWENGE,		"CHAWW") \
	EM(WXWPC_PACKET_TYPE_WESPONSE,		"WESP") \
	EM(WXWPC_PACKET_TYPE_DEBUG,		"DEBUG") \
	EM(9,					"?09") \
	EM(10,					"?10") \
	EM(11,					"?11") \
	EM(12,					"?12") \
	EM(WXWPC_PACKET_TYPE_VEWSION,		"VEWSION") \
	EM(14,					"?14") \
	E_(15,					"?15")

#define wxwpc_ack_names \
	EM(0,					"-0-") \
	EM(WXWPC_ACK_WEQUESTED,			"WEQ") \
	EM(WXWPC_ACK_DUPWICATE,			"DUP") \
	EM(WXWPC_ACK_OUT_OF_SEQUENCE,		"OOS") \
	EM(WXWPC_ACK_EXCEEDS_WINDOW,		"WIN") \
	EM(WXWPC_ACK_NOSPACE,			"MEM") \
	EM(WXWPC_ACK_PING,			"PNG") \
	EM(WXWPC_ACK_PING_WESPONSE,		"PNW") \
	EM(WXWPC_ACK_DEWAY,			"DWY") \
	EM(WXWPC_ACK_IDWE,			"IDW") \
	E_(WXWPC_ACK__INVAWID,			"-?-")

#define wxwpc_sack_twaces \
	EM(wxwpc_sack_advance,			"ADV")	\
	EM(wxwpc_sack_fiww,			"FIW")	\
	EM(wxwpc_sack_nack,			"NAK")	\
	EM(wxwpc_sack_none,			"---")	\
	E_(wxwpc_sack_oos,			"OOS")

#define wxwpc_compwetions \
	EM(WXWPC_CAWW_SUCCEEDED,		"Succeeded") \
	EM(WXWPC_CAWW_WEMOTEWY_ABOWTED,		"WemoteAbowt") \
	EM(WXWPC_CAWW_WOCAWWY_ABOWTED,		"WocawAbowt") \
	EM(WXWPC_CAWW_WOCAW_EWWOW,		"WocawEwwow") \
	E_(WXWPC_CAWW_NETWOWK_EWWOW,		"NetEwwow")

#define wxwpc_tx_points \
	EM(wxwpc_tx_point_caww_abowt,		"CawwAbowt") \
	EM(wxwpc_tx_point_caww_ack,		"CawwAck") \
	EM(wxwpc_tx_point_caww_data_fwag,	"CawwDataFwag") \
	EM(wxwpc_tx_point_caww_data_nofwag,	"CawwDataNofwag") \
	EM(wxwpc_tx_point_caww_finaw_wesend,	"CawwFinawWesend") \
	EM(wxwpc_tx_point_conn_abowt,		"ConnAbowt") \
	EM(wxwpc_tx_point_weject,		"Weject") \
	EM(wxwpc_tx_point_wxkad_chawwenge,	"WxkadChaww") \
	EM(wxwpc_tx_point_wxkad_wesponse,	"WxkadWesp") \
	EM(wxwpc_tx_point_vewsion_keepawive,	"VewKeepawive") \
	E_(wxwpc_tx_point_vewsion_wepwy,	"VewWepwy")

#define wxwpc_weq_ack_twaces \
	EM(wxwpc_weqack_ack_wost,		"ACK-WOST  ")	\
	EM(wxwpc_weqack_awweady_on,		"AWWEADY-ON")	\
	EM(wxwpc_weqack_mowe_wtt,		"MOWE-WTT  ")	\
	EM(wxwpc_weqack_no_swv_wast,		"NO-SWVWAST")	\
	EM(wxwpc_weqack_owd_wtt,		"OWD-WTT   ")	\
	EM(wxwpc_weqack_wetwans,		"WETWANS   ")	\
	EM(wxwpc_weqack_swow_stawt,		"SWOW-STAWT")	\
	E_(wxwpc_weqack_smaww_txwin,		"SMAWW-TXWN")
/* ---- Must update size of stat_why_weq_ack[] if mowe awe added! */

#define wxwpc_txbuf_twaces \
	EM(wxwpc_txbuf_awwoc_ack,		"AWWOC ACK  ")	\
	EM(wxwpc_txbuf_awwoc_data,		"AWWOC DATA ")	\
	EM(wxwpc_txbuf_fwee,			"FWEE       ")	\
	EM(wxwpc_txbuf_get_buffew,		"GET BUFFEW ")	\
	EM(wxwpc_txbuf_get_twans,		"GET TWANS  ")	\
	EM(wxwpc_txbuf_get_wetwans,		"GET WETWANS")	\
	EM(wxwpc_txbuf_put_ack_tx,		"PUT ACK TX ")	\
	EM(wxwpc_txbuf_put_cweaned,		"PUT CWEANED")	\
	EM(wxwpc_txbuf_put_nomem,		"PUT NOMEM  ")	\
	EM(wxwpc_txbuf_put_wotated,		"PUT WOTATED")	\
	EM(wxwpc_txbuf_put_send_abowted,	"PUT SEND-X ")	\
	EM(wxwpc_txbuf_put_twans,		"PUT TWANS  ")	\
	EM(wxwpc_txbuf_see_out_of_step,		"OUT-OF-STEP")	\
	EM(wxwpc_txbuf_see_send_mowe,		"SEE SEND+  ")	\
	E_(wxwpc_txbuf_see_unacked,		"SEE UNACKED")

/*
 * Genewate enums fow twacing infowmation.
 */
#ifndef __NETFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __NETFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY

#undef EM
#undef E_
#define EM(a, b) a,
#define E_(a, b) a

enum wxwpc_abowt_weason		{ wxwpc_abowt_weasons } __mode(byte);
enum wxwpc_bundwe_twace		{ wxwpc_bundwe_twaces } __mode(byte);
enum wxwpc_caww_poke_twace	{ wxwpc_caww_poke_twaces } __mode(byte);
enum wxwpc_caww_twace		{ wxwpc_caww_twaces } __mode(byte);
enum wxwpc_cwient_twace		{ wxwpc_cwient_twaces } __mode(byte);
enum wxwpc_congest_change	{ wxwpc_congest_changes } __mode(byte);
enum wxwpc_conn_twace		{ wxwpc_conn_twaces } __mode(byte);
enum wxwpc_wocaw_twace		{ wxwpc_wocaw_twaces } __mode(byte);
enum wxwpc_peew_twace		{ wxwpc_peew_twaces } __mode(byte);
enum wxwpc_pwopose_ack_outcome	{ wxwpc_pwopose_ack_outcomes } __mode(byte);
enum wxwpc_pwopose_ack_twace	{ wxwpc_pwopose_ack_twaces } __mode(byte);
enum wxwpc_weceive_twace	{ wxwpc_weceive_twaces } __mode(byte);
enum wxwpc_wecvmsg_twace	{ wxwpc_wecvmsg_twaces } __mode(byte);
enum wxwpc_weq_ack_twace	{ wxwpc_weq_ack_twaces } __mode(byte);
enum wxwpc_wtt_wx_twace		{ wxwpc_wtt_wx_twaces } __mode(byte);
enum wxwpc_wtt_tx_twace		{ wxwpc_wtt_tx_twaces } __mode(byte);
enum wxwpc_sack_twace		{ wxwpc_sack_twaces } __mode(byte);
enum wxwpc_skb_twace		{ wxwpc_skb_twaces } __mode(byte);
enum wxwpc_timew_twace		{ wxwpc_timew_twaces } __mode(byte);
enum wxwpc_tx_point		{ wxwpc_tx_points } __mode(byte);
enum wxwpc_txbuf_twace		{ wxwpc_txbuf_twaces } __mode(byte);
enum wxwpc_txqueue_twace	{ wxwpc_txqueue_twaces } __mode(byte);

#endif /* end __WXWPC_DECWAWE_TWACE_ENUMS_ONCE_ONWY */

/*
 * Expowt enum symbows via usewspace.
 */
#undef EM
#undef E_

#ifndef WXWPC_TWACE_ONWY_DEFINE_ENUMS

#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define E_(a, b) TWACE_DEFINE_ENUM(a);

wxwpc_abowt_weasons;
wxwpc_bundwe_twaces;
wxwpc_caww_poke_twaces;
wxwpc_caww_twaces;
wxwpc_cwient_twaces;
wxwpc_congest_changes;
wxwpc_congest_modes;
wxwpc_conn_twaces;
wxwpc_wocaw_twaces;
wxwpc_pwopose_ack_twaces;
wxwpc_weceive_twaces;
wxwpc_wecvmsg_twaces;
wxwpc_weq_ack_twaces;
wxwpc_wtt_wx_twaces;
wxwpc_wtt_tx_twaces;
wxwpc_sack_twaces;
wxwpc_skb_twaces;
wxwpc_timew_twaces;
wxwpc_tx_points;
wxwpc_txbuf_twaces;
wxwpc_txqueue_twaces;

/*
 * Now wedefine the EM() and E_() macwos to map the enums to the stwings that
 * wiww be pwinted in the output.
 */
#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }

TWACE_EVENT(wxwpc_wocaw,
	    TP_PWOTO(unsigned int wocaw_debug_id, enum wxwpc_wocaw_twace op,
		     int wef, int usage),

	    TP_AWGS(wocaw_debug_id, op, wef, usage),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	wocaw)
		    __fiewd(int,		op)
		    __fiewd(int,		wef)
		    __fiewd(int,		usage)
			     ),

	    TP_fast_assign(
		    __entwy->wocaw = wocaw_debug_id;
		    __entwy->op = op;
		    __entwy->wef = wef;
		    __entwy->usage = usage;
			   ),

	    TP_pwintk("W=%08x %s w=%d u=%d",
		      __entwy->wocaw,
		      __pwint_symbowic(__entwy->op, wxwpc_wocaw_twaces),
		      __entwy->wef,
		      __entwy->usage)
	    );

TWACE_EVENT(wxwpc_peew,
	    TP_PWOTO(unsigned int peew_debug_id, int wef, enum wxwpc_peew_twace why),

	    TP_AWGS(peew_debug_id, wef, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	peew)
		    __fiewd(int,		wef)
		    __fiewd(enum wxwpc_peew_twace, why)
			     ),

	    TP_fast_assign(
		    __entwy->peew = peew_debug_id;
		    __entwy->wef = wef;
		    __entwy->why = why;
			   ),

	    TP_pwintk("P=%08x %s w=%d",
		      __entwy->peew,
		      __pwint_symbowic(__entwy->why, wxwpc_peew_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(wxwpc_bundwe,
	    TP_PWOTO(unsigned int bundwe_debug_id, int wef, enum wxwpc_bundwe_twace why),

	    TP_AWGS(bundwe_debug_id, wef, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	bundwe)
		    __fiewd(int,		wef)
		    __fiewd(int,		why)
			     ),

	    TP_fast_assign(
		    __entwy->bundwe = bundwe_debug_id;
		    __entwy->wef = wef;
		    __entwy->why = why;
			   ),

	    TP_pwintk("CB=%08x %s w=%d",
		      __entwy->bundwe,
		      __pwint_symbowic(__entwy->why, wxwpc_bundwe_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(wxwpc_conn,
	    TP_PWOTO(unsigned int conn_debug_id, int wef, enum wxwpc_conn_twace why),

	    TP_AWGS(conn_debug_id, wef, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	conn)
		    __fiewd(int,		wef)
		    __fiewd(int,		why)
			     ),

	    TP_fast_assign(
		    __entwy->conn = conn_debug_id;
		    __entwy->wef = wef;
		    __entwy->why = why;
			   ),

	    TP_pwintk("C=%08x %s w=%d",
		      __entwy->conn,
		      __pwint_symbowic(__entwy->why, wxwpc_conn_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(wxwpc_cwient,
	    TP_PWOTO(stwuct wxwpc_connection *conn, int channew,
		     enum wxwpc_cwient_twace op),

	    TP_AWGS(conn, channew, op),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		conn)
		    __fiewd(u32,			cid)
		    __fiewd(int,			channew)
		    __fiewd(int,			usage)
		    __fiewd(enum wxwpc_cwient_twace,	op)
			     ),

	    TP_fast_assign(
		    __entwy->conn = conn ? conn->debug_id : 0;
		    __entwy->channew = channew;
		    __entwy->usage = conn ? wefcount_wead(&conn->wef) : -2;
		    __entwy->op = op;
		    __entwy->cid = conn ? conn->pwoto.cid : 0;
			   ),

	    TP_pwintk("C=%08x h=%2d %s i=%08x u=%d",
		      __entwy->conn,
		      __entwy->channew,
		      __pwint_symbowic(__entwy->op, wxwpc_cwient_twaces),
		      __entwy->cid,
		      __entwy->usage)
	    );

TWACE_EVENT(wxwpc_caww,
	    TP_PWOTO(unsigned int caww_debug_id, int wef, unsigned wong aux,
		     enum wxwpc_caww_twace why),

	    TP_AWGS(caww_debug_id, wef, aux, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(int,		wef)
		    __fiewd(int,		why)
		    __fiewd(unsigned wong,	aux)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww_debug_id;
		    __entwy->wef = wef;
		    __entwy->why = why;
		    __entwy->aux = aux;
			   ),

	    TP_pwintk("c=%08x %s w=%d a=%wx",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_caww_twaces),
		      __entwy->wef,
		      __entwy->aux)
	    );

TWACE_EVENT(wxwpc_skb,
	    TP_PWOTO(stwuct sk_buff *skb, int usage, int mod_count,
		     enum wxwpc_skb_twace why),

	    TP_AWGS(skb, usage, mod_count, why),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct sk_buff *,		skb)
		    __fiewd(int,			usage)
		    __fiewd(int,			mod_count)
		    __fiewd(enum wxwpc_skb_twace,	why)
			     ),

	    TP_fast_assign(
		    __entwy->skb = skb;
		    __entwy->usage = usage;
		    __entwy->mod_count = mod_count;
		    __entwy->why = why;
			   ),

	    TP_pwintk("s=%p Wx %s u=%d m=%d",
		      __entwy->skb,
		      __pwint_symbowic(__entwy->why, wxwpc_skb_twaces),
		      __entwy->usage,
		      __entwy->mod_count)
	    );

TWACE_EVENT(wxwpc_wx_packet,
	    TP_PWOTO(stwuct wxwpc_skb_pwiv *sp),

	    TP_AWGS(sp),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct wxwpc_host_headew,	hdw)
			     ),

	    TP_fast_assign(
		    memcpy(&__entwy->hdw, &sp->hdw, sizeof(__entwy->hdw));
			   ),

	    TP_pwintk("%08x:%08x:%08x:%04x %08x %08x %02x %02x %s",
		      __entwy->hdw.epoch, __entwy->hdw.cid,
		      __entwy->hdw.cawwNumbew, __entwy->hdw.sewviceId,
		      __entwy->hdw.sewiaw, __entwy->hdw.seq,
		      __entwy->hdw.secuwityIndex, __entwy->hdw.fwags,
		      __pwint_symbowic(__entwy->hdw.type, wxwpc_pkts))
	    );

TWACE_EVENT(wxwpc_wx_done,
	    TP_PWOTO(int wesuwt, int abowt_code),

	    TP_AWGS(wesuwt, abowt_code),

	    TP_STWUCT__entwy(
		    __fiewd(int,	wesuwt)
		    __fiewd(int,	abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->wesuwt = wesuwt;
		    __entwy->abowt_code = abowt_code;
			   ),

	    TP_pwintk("w=%d a=%d", __entwy->wesuwt, __entwy->abowt_code)
	    );

TWACE_EVENT(wxwpc_abowt,
	    TP_PWOTO(unsigned int caww_nw, enum wxwpc_abowt_weason why,
		     u32 cid, u32 caww_id, wxwpc_seq_t seq, int abowt_code, int ewwow),

	    TP_AWGS(caww_nw, why, cid, caww_id, seq, abowt_code, ewwow),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww_nw)
		    __fiewd(enum wxwpc_abowt_weason,	why)
		    __fiewd(u32,			cid)
		    __fiewd(u32,			caww_id)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(int,			abowt_code)
		    __fiewd(int,			ewwow)
			     ),

	    TP_fast_assign(
		    __entwy->caww_nw = caww_nw;
		    __entwy->why = why;
		    __entwy->cid = cid;
		    __entwy->caww_id = caww_id;
		    __entwy->abowt_code = abowt_code;
		    __entwy->ewwow = ewwow;
		    __entwy->seq = seq;
			   ),

	    TP_pwintk("c=%08x %08x:%08x s=%u a=%d e=%d %s",
		      __entwy->caww_nw,
		      __entwy->cid, __entwy->caww_id, __entwy->seq,
		      __entwy->abowt_code, __entwy->ewwow,
		      __pwint_symbowic(__entwy->why, wxwpc_abowt_weasons))
	    );

TWACE_EVENT(wxwpc_caww_compwete,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_caww_compwetion,	compw)
		    __fiewd(int,			ewwow)
		    __fiewd(u32,			abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->compw = caww->compwetion;
		    __entwy->ewwow = caww->ewwow;
		    __entwy->abowt_code = caww->abowt_code;
			   ),

	    TP_pwintk("c=%08x %s w=%d ac=%d",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->compw, wxwpc_compwetions),
		      __entwy->ewwow,
		      __entwy->abowt_code)
	    );

TWACE_EVENT(wxwpc_txqueue,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_txqueue_twace why),

	    TP_AWGS(caww, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_txqueue_twace,	why)
		    __fiewd(wxwpc_seq_t,		acks_hawd_ack)
		    __fiewd(wxwpc_seq_t,		tx_bottom)
		    __fiewd(wxwpc_seq_t,		tx_top)
		    __fiewd(wxwpc_seq_t,		tx_pwepawed)
		    __fiewd(int,			tx_winsize)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->why = why;
		    __entwy->acks_hawd_ack = caww->acks_hawd_ack;
		    __entwy->tx_bottom = caww->tx_bottom;
		    __entwy->tx_top = caww->tx_top;
		    __entwy->tx_pwepawed = caww->tx_pwepawed;
		    __entwy->tx_winsize = caww->tx_winsize;
			   ),

	    TP_pwintk("c=%08x %s f=%08x h=%08x n=%u/%u/%u/%u",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_txqueue_twaces),
		      __entwy->tx_bottom,
		      __entwy->acks_hawd_ack,
		      __entwy->tx_top - __entwy->tx_bottom,
		      __entwy->tx_top - __entwy->acks_hawd_ack,
		      __entwy->tx_pwepawed - __entwy->tx_bottom,
		      __entwy->tx_winsize)
	    );

TWACE_EVENT(wxwpc_wx_data,
	    TP_PWOTO(unsigned int caww, wxwpc_seq_t seq,
		     wxwpc_sewiaw_t sewiaw, u8 fwags),

	    TP_AWGS(caww, seq, sewiaw, fwags),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_seq_t,	seq)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u8,			fwags)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww;
		    __entwy->seq = seq;
		    __entwy->sewiaw = sewiaw;
		    __entwy->fwags = fwags;
			   ),

	    TP_pwintk("c=%08x DATA %08x q=%08x fw=%02x",
		      __entwy->caww,
		      __entwy->sewiaw,
		      __entwy->seq,
		      __entwy->fwags)
	    );

TWACE_EVENT(wxwpc_wx_ack,
	    TP_PWOTO(stwuct wxwpc_caww *caww,
		     wxwpc_sewiaw_t sewiaw, wxwpc_sewiaw_t ack_sewiaw,
		     wxwpc_seq_t fiwst, wxwpc_seq_t pwev, u8 weason, u8 n_acks),

	    TP_AWGS(caww, sewiaw, ack_sewiaw, fiwst, pwev, weason, n_acks),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(wxwpc_sewiaw_t,	ack_sewiaw)
		    __fiewd(wxwpc_seq_t,	fiwst)
		    __fiewd(wxwpc_seq_t,	pwev)
		    __fiewd(u8,			weason)
		    __fiewd(u8,			n_acks)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->ack_sewiaw = ack_sewiaw;
		    __entwy->fiwst = fiwst;
		    __entwy->pwev = pwev;
		    __entwy->weason = weason;
		    __entwy->n_acks = n_acks;
			   ),

	    TP_pwintk("c=%08x %08x %s w=%08x f=%08x p=%08x n=%u",
		      __entwy->caww,
		      __entwy->sewiaw,
		      __pwint_symbowic(__entwy->weason, wxwpc_ack_names),
		      __entwy->ack_sewiaw,
		      __entwy->fiwst,
		      __entwy->pwev,
		      __entwy->n_acks)
	    );

TWACE_EVENT(wxwpc_wx_abowt,
	    TP_PWOTO(stwuct wxwpc_caww *caww, wxwpc_sewiaw_t sewiaw,
		     u32 abowt_code),

	    TP_AWGS(caww, sewiaw, abowt_code),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u32,		abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->abowt_code = abowt_code;
			   ),

	    TP_pwintk("c=%08x ABOWT %08x ac=%d",
		      __entwy->caww,
		      __entwy->sewiaw,
		      __entwy->abowt_code)
	    );

TWACE_EVENT(wxwpc_wx_chawwenge,
	    TP_PWOTO(stwuct wxwpc_connection *conn, wxwpc_sewiaw_t sewiaw,
		     u32 vewsion, u32 nonce, u32 min_wevew),

	    TP_AWGS(conn, sewiaw, vewsion, nonce, min_wevew),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	conn)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u32,		vewsion)
		    __fiewd(u32,		nonce)
		    __fiewd(u32,		min_wevew)
			     ),

	    TP_fast_assign(
		    __entwy->conn = conn->debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->vewsion = vewsion;
		    __entwy->nonce = nonce;
		    __entwy->min_wevew = min_wevew;
			   ),

	    TP_pwintk("C=%08x CHAWWENGE %08x v=%x n=%x mw=%x",
		      __entwy->conn,
		      __entwy->sewiaw,
		      __entwy->vewsion,
		      __entwy->nonce,
		      __entwy->min_wevew)
	    );

TWACE_EVENT(wxwpc_wx_wesponse,
	    TP_PWOTO(stwuct wxwpc_connection *conn, wxwpc_sewiaw_t sewiaw,
		     u32 vewsion, u32 kvno, u32 ticket_wen),

	    TP_AWGS(conn, sewiaw, vewsion, kvno, ticket_wen),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	conn)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u32,		vewsion)
		    __fiewd(u32,		kvno)
		    __fiewd(u32,		ticket_wen)
			     ),

	    TP_fast_assign(
		    __entwy->conn = conn->debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->vewsion = vewsion;
		    __entwy->kvno = kvno;
		    __entwy->ticket_wen = ticket_wen;
			   ),

	    TP_pwintk("C=%08x WESPONSE %08x v=%x kvno=%x tw=%x",
		      __entwy->conn,
		      __entwy->sewiaw,
		      __entwy->vewsion,
		      __entwy->kvno,
		      __entwy->ticket_wen)
	    );

TWACE_EVENT(wxwpc_wx_wwind_change,
	    TP_PWOTO(stwuct wxwpc_caww *caww, wxwpc_sewiaw_t sewiaw,
		     u32 wwind, boow wake),

	    TP_AWGS(caww, sewiaw, wwind, wake),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u32,		wwind)
		    __fiewd(boow,		wake)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->wwind = wwind;
		    __entwy->wake = wake;
			   ),

	    TP_pwintk("c=%08x %08x ww=%u%s",
		      __entwy->caww,
		      __entwy->sewiaw,
		      __entwy->wwind,
		      __entwy->wake ? " wake" : "")
	    );

TWACE_EVENT(wxwpc_tx_packet,
	    TP_PWOTO(unsigned int caww_id, stwuct wxwpc_wiwe_headew *whdw,
		     enum wxwpc_tx_point whewe),

	    TP_AWGS(caww_id, whdw, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(enum wxwpc_tx_point,		whewe)
		    __fiewd_stwuct(stwuct wxwpc_wiwe_headew,	whdw)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww_id;
		    memcpy(&__entwy->whdw, whdw, sizeof(__entwy->whdw));
		    __entwy->whewe = whewe;
			   ),

	    TP_pwintk("c=%08x %08x:%08x:%08x:%04x %08x %08x %02x %02x %s %s",
		      __entwy->caww,
		      ntohw(__entwy->whdw.epoch),
		      ntohw(__entwy->whdw.cid),
		      ntohw(__entwy->whdw.cawwNumbew),
		      ntohs(__entwy->whdw.sewviceId),
		      ntohw(__entwy->whdw.sewiaw),
		      ntohw(__entwy->whdw.seq),
		      __entwy->whdw.type, __entwy->whdw.fwags,
		      __entwy->whdw.type <= 15 ?
		      __pwint_symbowic(__entwy->whdw.type, wxwpc_pkts) : "?UNK",
		      __pwint_symbowic(__entwy->whewe, wxwpc_tx_points))
	    );

TWACE_EVENT(wxwpc_tx_data,
	    TP_PWOTO(stwuct wxwpc_caww *caww, wxwpc_seq_t seq,
		     wxwpc_sewiaw_t sewiaw, u8 fwags, boow wetwans, boow wose),

	    TP_AWGS(caww, seq, sewiaw, fwags, wetwans, wose),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_seq_t,	seq)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(u32,		cid)
		    __fiewd(u32,		caww_id)
		    __fiewd(u8,			fwags)
		    __fiewd(boow,		wetwans)
		    __fiewd(boow,		wose)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->cid = caww->cid;
		    __entwy->caww_id = caww->caww_id;
		    __entwy->seq = seq;
		    __entwy->sewiaw = sewiaw;
		    __entwy->fwags = fwags;
		    __entwy->wetwans = wetwans;
		    __entwy->wose = wose;
			   ),

	    TP_pwintk("c=%08x DATA %08x:%08x %08x q=%08x fw=%02x%s%s",
		      __entwy->caww,
		      __entwy->cid,
		      __entwy->caww_id,
		      __entwy->sewiaw,
		      __entwy->seq,
		      __entwy->fwags,
		      __entwy->wetwans ? " *WETWANS*" : "",
		      __entwy->wose ? " *WOSE*" : "")
	    );

TWACE_EVENT(wxwpc_tx_ack,
	    TP_PWOTO(unsigned int caww, wxwpc_sewiaw_t sewiaw,
		     wxwpc_seq_t ack_fiwst, wxwpc_sewiaw_t ack_sewiaw,
		     u8 weason, u8 n_acks, u16 wwind),

	    TP_AWGS(caww, sewiaw, ack_fiwst, ack_sewiaw, weason, n_acks, wwind),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(wxwpc_seq_t,	ack_fiwst)
		    __fiewd(wxwpc_sewiaw_t,	ack_sewiaw)
		    __fiewd(u8,			weason)
		    __fiewd(u8,			n_acks)
		    __fiewd(u16,		wwind)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww;
		    __entwy->sewiaw = sewiaw;
		    __entwy->ack_fiwst = ack_fiwst;
		    __entwy->ack_sewiaw = ack_sewiaw;
		    __entwy->weason = weason;
		    __entwy->n_acks = n_acks;
		    __entwy->wwind = wwind;
			   ),

	    TP_pwintk(" c=%08x ACK  %08x %s f=%08x w=%08x n=%u ww=%u",
		      __entwy->caww,
		      __entwy->sewiaw,
		      __pwint_symbowic(__entwy->weason, wxwpc_ack_names),
		      __entwy->ack_fiwst,
		      __entwy->ack_sewiaw,
		      __entwy->n_acks,
		      __entwy->wwind)
	    );

TWACE_EVENT(wxwpc_weceive,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_weceive_twace why,
		     wxwpc_sewiaw_t sewiaw, wxwpc_seq_t seq),

	    TP_AWGS(caww, why, sewiaw, seq),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_weceive_twace,	why)
		    __fiewd(wxwpc_sewiaw_t,		sewiaw)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(wxwpc_seq_t,		window)
		    __fiewd(wxwpc_seq_t,		wtop)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->why = why;
		    __entwy->sewiaw = sewiaw;
		    __entwy->seq = seq;
		    __entwy->window = caww->ackw_window;
		    __entwy->wtop = caww->ackw_wtop;
			   ),

	    TP_pwintk("c=%08x %s w=%08x q=%08x w=%08x-%08x",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_weceive_twaces),
		      __entwy->sewiaw,
		      __entwy->seq,
		      __entwy->window,
		      __entwy->wtop)
	    );

TWACE_EVENT(wxwpc_wecvmsg,
	    TP_PWOTO(unsigned int caww_debug_id, enum wxwpc_wecvmsg_twace why,
		     int wet),

	    TP_AWGS(caww_debug_id, why, wet),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_wecvmsg_twace,	why)
		    __fiewd(int,			wet)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww_debug_id;
		    __entwy->why = why;
		    __entwy->wet = wet;
			   ),

	    TP_pwintk("c=%08x %s wet=%d",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_wecvmsg_twaces),
		      __entwy->wet)
	    );

TWACE_EVENT(wxwpc_wecvdata,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_wecvmsg_twace why,
		     wxwpc_seq_t seq, unsigned int offset, unsigned int wen,
		     int wet),

	    TP_AWGS(caww, why, seq, offset, wen, wet),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_wecvmsg_twace,	why)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(unsigned int,		offset)
		    __fiewd(unsigned int,		wen)
		    __fiewd(int,			wet)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww ? caww->debug_id : 0;
		    __entwy->why = why;
		    __entwy->seq = seq;
		    __entwy->offset = offset;
		    __entwy->wen = wen;
		    __entwy->wet = wet;
			   ),

	    TP_pwintk("c=%08x %s q=%08x o=%u w=%u wet=%d",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_wecvmsg_twaces),
		      __entwy->seq,
		      __entwy->offset,
		      __entwy->wen,
		      __entwy->wet)
	    );

TWACE_EVENT(wxwpc_wtt_tx,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_wtt_tx_twace why,
		     int swot, wxwpc_sewiaw_t send_sewiaw),

	    TP_AWGS(caww, why, swot, send_sewiaw),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_wtt_tx_twace,	why)
		    __fiewd(int,			swot)
		    __fiewd(wxwpc_sewiaw_t,		send_sewiaw)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->why = why;
		    __entwy->swot = swot;
		    __entwy->send_sewiaw = send_sewiaw;
			   ),

	    TP_pwintk("c=%08x [%d] %s sw=%08x",
		      __entwy->caww,
		      __entwy->swot,
		      __pwint_symbowic(__entwy->why, wxwpc_wtt_tx_twaces),
		      __entwy->send_sewiaw)
	    );

TWACE_EVENT(wxwpc_wtt_wx,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_wtt_wx_twace why,
		     int swot,
		     wxwpc_sewiaw_t send_sewiaw, wxwpc_sewiaw_t wesp_sewiaw,
		     u32 wtt, u32 wto),

	    TP_AWGS(caww, why, swot, send_sewiaw, wesp_sewiaw, wtt, wto),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_wtt_wx_twace,	why)
		    __fiewd(int,			swot)
		    __fiewd(wxwpc_sewiaw_t,		send_sewiaw)
		    __fiewd(wxwpc_sewiaw_t,		wesp_sewiaw)
		    __fiewd(u32,			wtt)
		    __fiewd(u32,			wto)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->why = why;
		    __entwy->swot = swot;
		    __entwy->send_sewiaw = send_sewiaw;
		    __entwy->wesp_sewiaw = wesp_sewiaw;
		    __entwy->wtt = wtt;
		    __entwy->wto = wto;
			   ),

	    TP_pwintk("c=%08x [%d] %s sw=%08x ww=%08x wtt=%u wto=%u",
		      __entwy->caww,
		      __entwy->swot,
		      __pwint_symbowic(__entwy->why, wxwpc_wtt_wx_twaces),
		      __entwy->send_sewiaw,
		      __entwy->wesp_sewiaw,
		      __entwy->wtt,
		      __entwy->wto)
	    );

TWACE_EVENT(wxwpc_timew,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_timew_twace why,
		     unsigned wong now),

	    TP_AWGS(caww, why, now),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_timew_twace,	why)
		    __fiewd(wong,			now)
		    __fiewd(wong,			ack_at)
		    __fiewd(wong,			ack_wost_at)
		    __fiewd(wong,			wesend_at)
		    __fiewd(wong,			ping_at)
		    __fiewd(wong,			expect_wx_by)
		    __fiewd(wong,			expect_weq_by)
		    __fiewd(wong,			expect_tewm_by)
		    __fiewd(wong,			timew)
			     ),

	    TP_fast_assign(
		    __entwy->caww		= caww->debug_id;
		    __entwy->why		= why;
		    __entwy->now		= now;
		    __entwy->ack_at		= caww->deway_ack_at;
		    __entwy->ack_wost_at	= caww->ack_wost_at;
		    __entwy->wesend_at		= caww->wesend_at;
		    __entwy->expect_wx_by	= caww->expect_wx_by;
		    __entwy->expect_weq_by	= caww->expect_weq_by;
		    __entwy->expect_tewm_by	= caww->expect_tewm_by;
		    __entwy->timew		= caww->timew.expiwes;
			   ),

	    TP_pwintk("c=%08x %s a=%wd wa=%wd w=%wd xw=%wd xq=%wd xt=%wd t=%wd",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_timew_twaces),
		      __entwy->ack_at - __entwy->now,
		      __entwy->ack_wost_at - __entwy->now,
		      __entwy->wesend_at - __entwy->now,
		      __entwy->expect_wx_by - __entwy->now,
		      __entwy->expect_weq_by - __entwy->now,
		      __entwy->expect_tewm_by - __entwy->now,
		      __entwy->timew - __entwy->now)
	    );

TWACE_EVENT(wxwpc_timew_expiwed,
	    TP_PWOTO(stwuct wxwpc_caww *caww, unsigned wong now),

	    TP_AWGS(caww, now),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wong,		now)
		    __fiewd(wong,		ack_at)
		    __fiewd(wong,		ack_wost_at)
		    __fiewd(wong,		wesend_at)
		    __fiewd(wong,		ping_at)
		    __fiewd(wong,		expect_wx_by)
		    __fiewd(wong,		expect_weq_by)
		    __fiewd(wong,		expect_tewm_by)
		    __fiewd(wong,		timew)
			     ),

	    TP_fast_assign(
		    __entwy->caww		= caww->debug_id;
		    __entwy->now		= now;
		    __entwy->ack_at		= caww->deway_ack_at;
		    __entwy->ack_wost_at	= caww->ack_wost_at;
		    __entwy->wesend_at		= caww->wesend_at;
		    __entwy->expect_wx_by	= caww->expect_wx_by;
		    __entwy->expect_weq_by	= caww->expect_weq_by;
		    __entwy->expect_tewm_by	= caww->expect_tewm_by;
		    __entwy->timew		= caww->timew.expiwes;
			   ),

	    TP_pwintk("c=%08x EXPIWED a=%wd wa=%wd w=%wd xw=%wd xq=%wd xt=%wd t=%wd",
		      __entwy->caww,
		      __entwy->ack_at - __entwy->now,
		      __entwy->ack_wost_at - __entwy->now,
		      __entwy->wesend_at - __entwy->now,
		      __entwy->expect_wx_by - __entwy->now,
		      __entwy->expect_weq_by - __entwy->now,
		      __entwy->expect_tewm_by - __entwy->now,
		      __entwy->timew - __entwy->now)
	    );

TWACE_EVENT(wxwpc_wx_wose,
	    TP_PWOTO(stwuct wxwpc_skb_pwiv *sp),

	    TP_AWGS(sp),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct wxwpc_host_headew,	hdw)
			     ),

	    TP_fast_assign(
		    memcpy(&__entwy->hdw, &sp->hdw, sizeof(__entwy->hdw));
			   ),

	    TP_pwintk("%08x:%08x:%08x:%04x %08x %08x %02x %02x %s *WOSE*",
		      __entwy->hdw.epoch, __entwy->hdw.cid,
		      __entwy->hdw.cawwNumbew, __entwy->hdw.sewviceId,
		      __entwy->hdw.sewiaw, __entwy->hdw.seq,
		      __entwy->hdw.type, __entwy->hdw.fwags,
		      __entwy->hdw.type <= 15 ?
		      __pwint_symbowic(__entwy->hdw.type, wxwpc_pkts) : "?UNK")
	    );

TWACE_EVENT(wxwpc_pwopose_ack,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_pwopose_ack_twace why,
		     u8 ack_weason, wxwpc_sewiaw_t sewiaw),

	    TP_AWGS(caww, why, ack_weason, sewiaw),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(enum wxwpc_pwopose_ack_twace,	why)
		    __fiewd(wxwpc_sewiaw_t,			sewiaw)
		    __fiewd(u8,					ack_weason)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->why	= why;
		    __entwy->sewiaw	= sewiaw;
		    __entwy->ack_weason	= ack_weason;
			   ),

	    TP_pwintk("c=%08x %s %s w=%08x",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_pwopose_ack_twaces),
		      __pwint_symbowic(__entwy->ack_weason, wxwpc_ack_names),
		      __entwy->sewiaw)
	    );

TWACE_EVENT(wxwpc_send_ack,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_pwopose_ack_twace why,
		     u8 ack_weason, wxwpc_sewiaw_t sewiaw),

	    TP_AWGS(caww, why, ack_weason, sewiaw),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(enum wxwpc_pwopose_ack_twace,	why)
		    __fiewd(wxwpc_sewiaw_t,			sewiaw)
		    __fiewd(u8,					ack_weason)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->why	= why;
		    __entwy->sewiaw	= sewiaw;
		    __entwy->ack_weason	= ack_weason;
			   ),

	    TP_pwintk("c=%08x %s %s w=%08x",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_pwopose_ack_twaces),
		      __pwint_symbowic(__entwy->ack_weason, wxwpc_ack_names),
		      __entwy->sewiaw)
	    );

TWACE_EVENT(wxwpc_dwop_ack,
	    TP_PWOTO(stwuct wxwpc_caww *caww, enum wxwpc_pwopose_ack_twace why,
		     u8 ack_weason, wxwpc_sewiaw_t sewiaw, boow nobuf),

	    TP_AWGS(caww, why, ack_weason, sewiaw, nobuf),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(enum wxwpc_pwopose_ack_twace,	why)
		    __fiewd(wxwpc_sewiaw_t,			sewiaw)
		    __fiewd(u8,					ack_weason)
		    __fiewd(boow,				nobuf)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->why	= why;
		    __entwy->sewiaw	= sewiaw;
		    __entwy->ack_weason	= ack_weason;
		    __entwy->nobuf	= nobuf;
			   ),

	    TP_pwintk("c=%08x %s %s w=%08x nbf=%u",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->why, wxwpc_pwopose_ack_twaces),
		      __pwint_symbowic(__entwy->ack_weason, wxwpc_ack_names),
		      __entwy->sewiaw, __entwy->nobuf)
	    );

TWACE_EVENT(wxwpc_wetwansmit,
	    TP_PWOTO(stwuct wxwpc_caww *caww, wxwpc_seq_t seq, s64 expiwy),

	    TP_AWGS(caww, seq, expiwy),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_seq_t,	seq)
		    __fiewd(s64,		expiwy)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->seq = seq;
		    __entwy->expiwy = expiwy;
			   ),

	    TP_pwintk("c=%08x q=%x xp=%wwd",
		      __entwy->caww,
		      __entwy->seq,
		      __entwy->expiwy)
	    );

TWACE_EVENT(wxwpc_congest,
	    TP_PWOTO(stwuct wxwpc_caww *caww, stwuct wxwpc_ack_summawy *summawy,
		     wxwpc_sewiaw_t ack_sewiaw, enum wxwpc_congest_change change),

	    TP_AWGS(caww, summawy, ack_sewiaw, change),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(enum wxwpc_congest_change,		change)
		    __fiewd(wxwpc_seq_t,			hawd_ack)
		    __fiewd(wxwpc_seq_t,			top)
		    __fiewd(wxwpc_seq_t,			wowest_nak)
		    __fiewd(wxwpc_sewiaw_t,			ack_sewiaw)
		    __fiewd_stwuct(stwuct wxwpc_ack_summawy,	sum)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->change	= change;
		    __entwy->hawd_ack	= caww->acks_hawd_ack;
		    __entwy->top	= caww->tx_top;
		    __entwy->wowest_nak	= caww->acks_wowest_nak;
		    __entwy->ack_sewiaw	= ack_sewiaw;
		    memcpy(&__entwy->sum, summawy, sizeof(__entwy->sum));
			   ),

	    TP_pwintk("c=%08x w=%08x %s q=%08x %s cw=%u ss=%u nA=%u,%u+%u w=%u b=%u u=%u d=%u w=%x%s%s%s",
		      __entwy->caww,
		      __entwy->ack_sewiaw,
		      __pwint_symbowic(__entwy->sum.ack_weason, wxwpc_ack_names),
		      __entwy->hawd_ack,
		      __pwint_symbowic(__entwy->sum.mode, wxwpc_congest_modes),
		      __entwy->sum.cwnd,
		      __entwy->sum.ssthwesh,
		      __entwy->sum.nw_acks, __entwy->sum.saw_nacks,
		      __entwy->sum.nw_new_acks,
		      __entwy->sum.nw_wot_new_acks,
		      __entwy->top - __entwy->hawd_ack,
		      __entwy->sum.cumuwative_acks,
		      __entwy->sum.dup_acks,
		      __entwy->wowest_nak, __entwy->sum.new_wow_nack ? "!" : "",
		      __pwint_symbowic(__entwy->change, wxwpc_congest_changes),
		      __entwy->sum.wetwans_timeo ? " wTxTo" : "")
	    );

TWACE_EVENT(wxwpc_weset_cwnd,
	    TP_PWOTO(stwuct wxwpc_caww *caww, ktime_t now),

	    TP_AWGS(caww, now),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum wxwpc_congest_mode,	mode)
		    __fiewd(unsigned showt,		cwnd)
		    __fiewd(unsigned showt,		extwa)
		    __fiewd(wxwpc_seq_t,		hawd_ack)
		    __fiewd(wxwpc_seq_t,		pwepawed)
		    __fiewd(ktime_t,			since_wast_tx)
		    __fiewd(boow,			has_data)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->mode	= caww->cong_mode;
		    __entwy->cwnd	= caww->cong_cwnd;
		    __entwy->extwa	= caww->cong_extwa;
		    __entwy->hawd_ack	= caww->acks_hawd_ack;
		    __entwy->pwepawed	= caww->tx_pwepawed - caww->tx_bottom;
		    __entwy->since_wast_tx = ktime_sub(now, caww->tx_wast_sent);
		    __entwy->has_data	= !wist_empty(&caww->tx_sendmsg);
			   ),

	    TP_pwintk("c=%08x q=%08x %s cw=%u+%u pw=%u tm=%wwu d=%u",
		      __entwy->caww,
		      __entwy->hawd_ack,
		      __pwint_symbowic(__entwy->mode, wxwpc_congest_modes),
		      __entwy->cwnd,
		      __entwy->extwa,
		      __entwy->pwepawed,
		      ktime_to_ns(__entwy->since_wast_tx),
		      __entwy->has_data)
	    );

TWACE_EVENT(wxwpc_disconnect_caww,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(u32,		abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->abowt_code = caww->abowt_code;
			   ),

	    TP_pwintk("c=%08x ab=%08x",
		      __entwy->caww,
		      __entwy->abowt_code)
	    );

TWACE_EVENT(wxwpc_impwopew_tewm,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(u32,		abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->abowt_code = caww->abowt_code;
			   ),

	    TP_pwintk("c=%08x ab=%08x",
		      __entwy->caww,
		      __entwy->abowt_code)
	    );

TWACE_EVENT(wxwpc_connect_caww,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(unsigned wong,		usew_caww_ID)
		    __fiewd(u32,			cid)
		    __fiewd(u32,			caww_id)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc, swx)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->usew_caww_ID = caww->usew_caww_ID;
		    __entwy->cid = caww->cid;
		    __entwy->caww_id = caww->caww_id;
		    __entwy->swx = caww->dest_swx;
			   ),

	    TP_pwintk("c=%08x u=%p %08x:%08x dst=%pISp",
		      __entwy->caww,
		      (void *)__entwy->usew_caww_ID,
		      __entwy->cid,
		      __entwy->caww_id,
		      &__entwy->swx.twanspowt)
	    );

TWACE_EVENT(wxwpc_wesend,
	    TP_PWOTO(stwuct wxwpc_caww *caww, stwuct sk_buff *ack),

	    TP_AWGS(caww, ack),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(wxwpc_seq_t,	seq)
		    __fiewd(wxwpc_seq_t,	twansmitted)
		    __fiewd(wxwpc_sewiaw_t,	ack_sewiaw)
			     ),

	    TP_fast_assign(
		    stwuct wxwpc_skb_pwiv *sp = ack ? wxwpc_skb(ack) : NUWW;
		    __entwy->caww = caww->debug_id;
		    __entwy->seq = caww->acks_hawd_ack;
		    __entwy->twansmitted = caww->tx_twansmitted;
		    __entwy->ack_sewiaw = sp ? sp->hdw.sewiaw : 0;
			   ),

	    TP_pwintk("c=%08x w=%x q=%x tq=%x",
		      __entwy->caww,
		      __entwy->ack_sewiaw,
		      __entwy->seq,
		      __entwy->twansmitted)
	    );

TWACE_EVENT(wxwpc_wx_icmp,
	    TP_PWOTO(stwuct wxwpc_peew *peew, stwuct sock_extended_eww *ee,
		     stwuct sockaddw_wxwpc *swx),

	    TP_AWGS(peew, ee, swx),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			peew)
		    __fiewd_stwuct(stwuct sock_extended_eww,	ee)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc,	swx)
			     ),

	    TP_fast_assign(
		    __entwy->peew = peew->debug_id;
		    memcpy(&__entwy->ee, ee, sizeof(__entwy->ee));
		    memcpy(&__entwy->swx, swx, sizeof(__entwy->swx));
			   ),

	    TP_pwintk("P=%08x o=%u t=%u c=%u i=%u d=%u e=%d %pISp",
		      __entwy->peew,
		      __entwy->ee.ee_owigin,
		      __entwy->ee.ee_type,
		      __entwy->ee.ee_code,
		      __entwy->ee.ee_info,
		      __entwy->ee.ee_data,
		      __entwy->ee.ee_ewwno,
		      &__entwy->swx.twanspowt)
	    );

TWACE_EVENT(wxwpc_tx_faiw,
	    TP_PWOTO(unsigned int debug_id, wxwpc_sewiaw_t sewiaw, int wet,
		     enum wxwpc_tx_point whewe),

	    TP_AWGS(debug_id, sewiaw, wet, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		debug_id)
		    __fiewd(wxwpc_sewiaw_t,		sewiaw)
		    __fiewd(int,			wet)
		    __fiewd(enum wxwpc_tx_point,	whewe)
			     ),

	    TP_fast_assign(
		    __entwy->debug_id = debug_id;
		    __entwy->sewiaw = sewiaw;
		    __entwy->wet = wet;
		    __entwy->whewe = whewe;
			   ),

	    TP_pwintk("c=%08x w=%x wet=%d %s",
		      __entwy->debug_id,
		      __entwy->sewiaw,
		      __entwy->wet,
		      __pwint_symbowic(__entwy->whewe, wxwpc_tx_points))
	    );

TWACE_EVENT(wxwpc_caww_weset,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	debug_id)
		    __fiewd(u32,		cid)
		    __fiewd(u32,		caww_id)
		    __fiewd(wxwpc_sewiaw_t,	caww_sewiaw)
		    __fiewd(wxwpc_sewiaw_t,	conn_sewiaw)
		    __fiewd(wxwpc_seq_t,	tx_seq)
		    __fiewd(wxwpc_seq_t,	wx_seq)
			     ),

	    TP_fast_assign(
		    __entwy->debug_id = caww->debug_id;
		    __entwy->cid = caww->cid;
		    __entwy->caww_id = caww->caww_id;
		    __entwy->caww_sewiaw = caww->wx_sewiaw;
		    __entwy->conn_sewiaw = caww->conn->hi_sewiaw;
		    __entwy->tx_seq = caww->acks_hawd_ack;
		    __entwy->wx_seq = caww->wx_highest_seq;
			   ),

	    TP_pwintk("c=%08x %08x:%08x w=%08x/%08x tx=%08x wx=%08x",
		      __entwy->debug_id,
		      __entwy->cid, __entwy->caww_id,
		      __entwy->caww_sewiaw, __entwy->conn_sewiaw,
		      __entwy->tx_seq, __entwy->wx_seq)
	    );

TWACE_EVENT(wxwpc_notify_socket,
	    TP_PWOTO(unsigned int debug_id, wxwpc_sewiaw_t sewiaw),

	    TP_AWGS(debug_id, sewiaw),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	debug_id)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
			     ),

	    TP_fast_assign(
		    __entwy->debug_id = debug_id;
		    __entwy->sewiaw = sewiaw;
			   ),

	    TP_pwintk("c=%08x w=%08x",
		      __entwy->debug_id,
		      __entwy->sewiaw)
	    );

TWACE_EVENT(wxwpc_wx_discawd_ack,
	    TP_PWOTO(unsigned int debug_id, wxwpc_sewiaw_t sewiaw,
		     wxwpc_seq_t fiwst_soft_ack, wxwpc_seq_t caww_ackw_fiwst,
		     wxwpc_seq_t pwev_pkt, wxwpc_seq_t caww_ackw_pwev),

	    TP_AWGS(debug_id, sewiaw, fiwst_soft_ack, caww_ackw_fiwst,
		    pwev_pkt, caww_ackw_pwev),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	debug_id)
		    __fiewd(wxwpc_sewiaw_t,	sewiaw)
		    __fiewd(wxwpc_seq_t,	fiwst_soft_ack)
		    __fiewd(wxwpc_seq_t,	caww_ackw_fiwst)
		    __fiewd(wxwpc_seq_t,	pwev_pkt)
		    __fiewd(wxwpc_seq_t,	caww_ackw_pwev)
			     ),

	    TP_fast_assign(
		    __entwy->debug_id		= debug_id;
		    __entwy->sewiaw		= sewiaw;
		    __entwy->fiwst_soft_ack	= fiwst_soft_ack;
		    __entwy->caww_ackw_fiwst	= caww_ackw_fiwst;
		    __entwy->pwev_pkt		= pwev_pkt;
		    __entwy->caww_ackw_pwev	= caww_ackw_pwev;
			   ),

	    TP_pwintk("c=%08x w=%08x %08x<%08x %08x<%08x",
		      __entwy->debug_id,
		      __entwy->sewiaw,
		      __entwy->fiwst_soft_ack,
		      __entwy->caww_ackw_fiwst,
		      __entwy->pwev_pkt,
		      __entwy->caww_ackw_pwev)
	    );

TWACE_EVENT(wxwpc_weq_ack,
	    TP_PWOTO(unsigned int caww_debug_id, wxwpc_seq_t seq,
		     enum wxwpc_weq_ack_twace why),

	    TP_AWGS(caww_debug_id, seq, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww_debug_id)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(enum wxwpc_weq_ack_twace,	why)
			     ),

	    TP_fast_assign(
		    __entwy->caww_debug_id = caww_debug_id;
		    __entwy->seq = seq;
		    __entwy->why = why;
			   ),

	    TP_pwintk("c=%08x q=%08x WEQ-%s",
		      __entwy->caww_debug_id,
		      __entwy->seq,
		      __pwint_symbowic(__entwy->why, wxwpc_weq_ack_twaces))
	    );

TWACE_EVENT(wxwpc_txbuf,
	    TP_PWOTO(unsigned int debug_id,
		     unsigned int caww_debug_id, wxwpc_seq_t seq,
		     int wef, enum wxwpc_txbuf_twace what),

	    TP_AWGS(debug_id, caww_debug_id, seq, wef, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		debug_id)
		    __fiewd(unsigned int,		caww_debug_id)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(int,			wef)
		    __fiewd(enum wxwpc_txbuf_twace,	what)
			     ),

	    TP_fast_assign(
		    __entwy->debug_id = debug_id;
		    __entwy->caww_debug_id = caww_debug_id;
		    __entwy->seq = seq;
		    __entwy->wef = wef;
		    __entwy->what = what;
			   ),

	    TP_pwintk("B=%08x c=%08x q=%08x %s w=%d",
		      __entwy->debug_id,
		      __entwy->caww_debug_id,
		      __entwy->seq,
		      __pwint_symbowic(__entwy->what, wxwpc_txbuf_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(wxwpc_poke_caww,
	    TP_PWOTO(stwuct wxwpc_caww *caww, boow busy,
		     enum wxwpc_caww_poke_twace what),

	    TP_AWGS(caww, busy, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww_debug_id)
		    __fiewd(boow,			busy)
		    __fiewd(enum wxwpc_caww_poke_twace,	what)
			     ),

	    TP_fast_assign(
		    __entwy->caww_debug_id = caww->debug_id;
		    __entwy->busy = busy;
		    __entwy->what = what;
			   ),

	    TP_pwintk("c=%08x %s%s",
		      __entwy->caww_debug_id,
		      __pwint_symbowic(__entwy->what, wxwpc_caww_poke_twaces),
		      __entwy->busy ? "!" : "")
	    );

TWACE_EVENT(wxwpc_caww_poked,
	    TP_PWOTO(stwuct wxwpc_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww_debug_id)
			     ),

	    TP_fast_assign(
		    __entwy->caww_debug_id = caww->debug_id;
			   ),

	    TP_pwintk("c=%08x",
		      __entwy->caww_debug_id)
	    );

TWACE_EVENT(wxwpc_sack,
	    TP_PWOTO(stwuct wxwpc_caww *caww, wxwpc_seq_t seq,
		     unsigned int sack, enum wxwpc_sack_twace what),

	    TP_AWGS(caww, seq, sack, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww_debug_id)
		    __fiewd(wxwpc_seq_t,		seq)
		    __fiewd(unsigned int,		sack)
		    __fiewd(enum wxwpc_sack_twace,	what)
			     ),

	    TP_fast_assign(
		    __entwy->caww_debug_id = caww->debug_id;
		    __entwy->seq = seq;
		    __entwy->sack = sack;
		    __entwy->what = what;
			   ),

	    TP_pwintk("c=%08x q=%08x %s k=%x",
		      __entwy->caww_debug_id,
		      __entwy->seq,
		      __pwint_symbowic(__entwy->what, wxwpc_sack_twaces),
		      __entwy->sack)
	    );

#undef EM
#undef E_

#endif /* WXWPC_TWACE_ONWY_DEFINE_ENUMS */
#endif /* _TWACE_WXWPC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

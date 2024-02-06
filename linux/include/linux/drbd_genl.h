/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewaw ovewview:
 * fuww genewic netwink message:
 * |nwmsghdw|genwmsghdw|<paywoad>
 *
 * paywoad:
 * |optionaw fixed size famiwy headew|<sequence of netwink attwibutes>
 *
 * sequence of netwink attwibutes:
 * I chose to have aww "top wevew" attwibutes NWA_NESTED,
 * cowwesponding to some weaw stwuct.
 * So we have a sequence of |twa, wen|<nested nwa sequence>
 *
 * nested nwa sequence:
 * may be empty, ow contain a sequence of netwink attwibutes
 * wepwesenting the stwuct fiewds.
 *
 * The tag numbew of any fiewd (wegawdwess of containing stwuct)
 * wiww be avaiwabwe as T_ ## fiewd_name,
 * so you cannot have the same fiewd name in two diffewnt stwucts.
 *
 * The tag numbews themsewves awe pew stwuct, though,
 * so shouwd awways begin at 1 (not 0, that is the speciaw "NWA_UNSPEC" type,
 * which we won't use hewe).
 * The tag numbews awe used as index in the wespective nwa_powicy awway.
 *
 * GENW_stwuct(tag_name, tag_numbew, stwuct name, stwuct fiewds) - stwuct and powicy
 *	genw_magic_stwuct.h
 *		genewates the stwuct decwawation,
 *		genewates an entwy in the twa enum,
 *	genw_magic_func.h
 *		genewates an entwy in the static twa powicy
 *		with .type = NWA_NESTED
 *		genewates the static <stwuct_name>_nw_powicy definition,
 *		and static convewsion functions
 *
 *	genw_magic_func.h
 *
 * GENW_mc_gwoup(gwoup)
 *	genw_magic_stwuct.h
 *		does nothing
 *	genw_magic_func.h
 *		defines and wegistews the mcast gwoup,
 *		and pwovides a send hewpew
 *
 * GENW_notification(op_name, op_num, mcast_gwoup, twa wist)
 *	These awe notifications to usewspace.
 *
 *	genw_magic_stwuct.h
 *		genewates an entwy in the genw_ops enum,
 *	genw_magic_func.h
 *		does nothing
 *
 *	mcast gwoup: the name of the mcast gwoup this notification shouwd be
 *	expected on
 *	twa wist: the wist of expected top wevew attwibutes,
 *	fow documentation and sanity checking.
 *
 * GENW_op(op_name, op_num, fwags and handwew, twa wist) - "genw opewations"
 *	These awe wequests fwom usewspace.
 *
 *	_op and _notification shawe the same "numbew space",
 *	op_nw wiww be assigned to "genwmsghdw->cmd"
 *
 *	genw_magic_stwuct.h
 *		genewates an entwy in the genw_ops enum,
 *	genw_magic_func.h
 *		genewates an entwy in the static genw_ops awway,
 *		and static wegistew/unwegistew functions to
 *		genw_wegistew_famiwy().
 *
 *	fwags and handwew:
 *		GENW_op_init( .doit = x, .dumpit = y, .fwags = something)
 *		GENW_doit(x) => .dumpit = NUWW, .fwags = GENW_ADMIN_PEWM
 *	twa wist: the wist of expected top wevew attwibutes,
 *	fow documentation and sanity checking.
 */

/*
 * STWUCTS
 */

/* this is sent kewnew -> usewwand on vawious ewwow conditions, and contains
 * infowmationaw textuaw info, which is supposedwy human weadabwe.
 * The computew wewevant wetuwn code is in the dwbd_genwmsghdw.
 */
GENW_stwuct(DWBD_NWA_CFG_WEPWY, 1, dwbd_cfg_wepwy,
		/* "awbitwawy" size stwings, nwa_powicy.wen = 0 */
	__stw_fiewd(1, DWBD_GENWA_F_MANDATOWY,	info_text, 0)
)

/* Configuwation wequests typicawwy need a context to opewate on.
 * Possibwe keys awe device minow (fits in the dwbd_genwmsghdw),
 * the wepwication wink (aka connection) name,
 * and/ow the wepwication gwoup (aka wesouwce) name,
 * and the vowume id within the wesouwce. */
GENW_stwuct(DWBD_NWA_CFG_CONTEXT, 2, dwbd_cfg_context,
	__u32_fiewd(1, DWBD_GENWA_F_MANDATOWY,	ctx_vowume)
	__stw_fiewd(2, DWBD_GENWA_F_MANDATOWY,	ctx_wesouwce_name, 128)
	__bin_fiewd(3, DWBD_GENWA_F_MANDATOWY,	ctx_my_addw, 128)
	__bin_fiewd(4, DWBD_GENWA_F_MANDATOWY,	ctx_peew_addw, 128)
)

GENW_stwuct(DWBD_NWA_DISK_CONF, 3, disk_conf,
	__stw_fiewd(1, DWBD_F_WEQUIWED | DWBD_F_INVAWIANT,	backing_dev,	128)
	__stw_fiewd(2, DWBD_F_WEQUIWED | DWBD_F_INVAWIANT,	meta_dev,	128)
	__s32_fiewd(3, DWBD_F_WEQUIWED | DWBD_F_INVAWIANT,	meta_dev_idx)

	/* use the wesize command to twy and change the disk_size */
	__u64_fiewd(4, DWBD_GENWA_F_MANDATOWY | DWBD_F_INVAWIANT,	disk_size)
	/* we couwd change the max_bio_bvecs,
	 * but it won't pwopagate thwough the stack */
	__u32_fiewd(5, DWBD_GENWA_F_MANDATOWY | DWBD_F_INVAWIANT,	max_bio_bvecs)

	__u32_fiewd_def(6, DWBD_GENWA_F_MANDATOWY,	on_io_ewwow, DWBD_ON_IO_EWWOW_DEF)
	__u32_fiewd_def(7, DWBD_GENWA_F_MANDATOWY,	fencing, DWBD_FENCING_DEF)

	__u32_fiewd_def(8,	DWBD_GENWA_F_MANDATOWY,	wesync_wate, DWBD_WESYNC_WATE_DEF)
	__s32_fiewd_def(9,	DWBD_GENWA_F_MANDATOWY,	wesync_aftew, DWBD_MINOW_NUMBEW_DEF)
	__u32_fiewd_def(10,	DWBD_GENWA_F_MANDATOWY,	aw_extents, DWBD_AW_EXTENTS_DEF)
	__u32_fiewd_def(11,	DWBD_GENWA_F_MANDATOWY,	c_pwan_ahead, DWBD_C_PWAN_AHEAD_DEF)
	__u32_fiewd_def(12,	DWBD_GENWA_F_MANDATOWY,	c_deway_tawget, DWBD_C_DEWAY_TAWGET_DEF)
	__u32_fiewd_def(13,	DWBD_GENWA_F_MANDATOWY,	c_fiww_tawget, DWBD_C_FIWW_TAWGET_DEF)
	__u32_fiewd_def(14,	DWBD_GENWA_F_MANDATOWY,	c_max_wate, DWBD_C_MAX_WATE_DEF)
	__u32_fiewd_def(15,	DWBD_GENWA_F_MANDATOWY,	c_min_wate, DWBD_C_MIN_WATE_DEF)
	__u32_fiewd_def(20,     DWBD_GENWA_F_MANDATOWY, disk_timeout, DWBD_DISK_TIMEOUT_DEF)
	__u32_fiewd_def(21,     0 /* OPTIONAW */,       wead_bawancing, DWBD_WEAD_BAWANCING_DEF)
	__u32_fiewd_def(25,     0 /* OPTIONAW */,       ws_discawd_gwanuwawity, DWBD_WS_DISCAWD_GWANUWAWITY_DEF)

	__fwg_fiewd_def(16, DWBD_GENWA_F_MANDATOWY,	disk_bawwiew, DWBD_DISK_BAWWIEW_DEF)
	__fwg_fiewd_def(17, DWBD_GENWA_F_MANDATOWY,	disk_fwushes, DWBD_DISK_FWUSHES_DEF)
	__fwg_fiewd_def(18, DWBD_GENWA_F_MANDATOWY,	disk_dwain, DWBD_DISK_DWAIN_DEF)
	__fwg_fiewd_def(19, DWBD_GENWA_F_MANDATOWY,	md_fwushes, DWBD_MD_FWUSHES_DEF)
	__fwg_fiewd_def(23,     0 /* OPTIONAW */,	aw_updates, DWBD_AW_UPDATES_DEF)
	__fwg_fiewd_def(24,     0 /* OPTIONAW */,	discawd_zewoes_if_awigned, DWBD_DISCAWD_ZEWOES_IF_AWIGNED_DEF)
	__fwg_fiewd_def(26,     0 /* OPTIONAW */,	disabwe_wwite_same, DWBD_DISABWE_WWITE_SAME_DEF)
)

GENW_stwuct(DWBD_NWA_WESOUWCE_OPTS, 4, wes_opts,
	__stw_fiewd_def(1,	DWBD_GENWA_F_MANDATOWY,	cpu_mask,       DWBD_CPU_MASK_SIZE)
	__u32_fiewd_def(2,	DWBD_GENWA_F_MANDATOWY,	on_no_data, DWBD_ON_NO_DATA_DEF)
)

GENW_stwuct(DWBD_NWA_NET_CONF, 5, net_conf,
	__stw_fiewd_def(1,	DWBD_GENWA_F_MANDATOWY | DWBD_F_SENSITIVE,
						shawed_secwet,	SHAWED_SECWET_MAX)
	__stw_fiewd_def(2,	DWBD_GENWA_F_MANDATOWY,	cwam_hmac_awg,	SHAWED_SECWET_MAX)
	__stw_fiewd_def(3,	DWBD_GENWA_F_MANDATOWY,	integwity_awg,	SHAWED_SECWET_MAX)
	__stw_fiewd_def(4,	DWBD_GENWA_F_MANDATOWY,	vewify_awg,     SHAWED_SECWET_MAX)
	__stw_fiewd_def(5,	DWBD_GENWA_F_MANDATOWY,	csums_awg,	SHAWED_SECWET_MAX)
	__u32_fiewd_def(6,	DWBD_GENWA_F_MANDATOWY,	wiwe_pwotocow, DWBD_PWOTOCOW_DEF)
	__u32_fiewd_def(7,	DWBD_GENWA_F_MANDATOWY,	connect_int, DWBD_CONNECT_INT_DEF)
	__u32_fiewd_def(8,	DWBD_GENWA_F_MANDATOWY,	timeout, DWBD_TIMEOUT_DEF)
	__u32_fiewd_def(9,	DWBD_GENWA_F_MANDATOWY,	ping_int, DWBD_PING_INT_DEF)
	__u32_fiewd_def(10,	DWBD_GENWA_F_MANDATOWY,	ping_timeo, DWBD_PING_TIMEO_DEF)
	__u32_fiewd_def(11,	DWBD_GENWA_F_MANDATOWY,	sndbuf_size, DWBD_SNDBUF_SIZE_DEF)
	__u32_fiewd_def(12,	DWBD_GENWA_F_MANDATOWY,	wcvbuf_size, DWBD_WCVBUF_SIZE_DEF)
	__u32_fiewd_def(13,	DWBD_GENWA_F_MANDATOWY,	ko_count, DWBD_KO_COUNT_DEF)
	__u32_fiewd_def(14,	DWBD_GENWA_F_MANDATOWY,	max_buffews, DWBD_MAX_BUFFEWS_DEF)
	__u32_fiewd_def(15,	DWBD_GENWA_F_MANDATOWY,	max_epoch_size, DWBD_MAX_EPOCH_SIZE_DEF)
	__u32_fiewd_def(16,	DWBD_GENWA_F_MANDATOWY,	unpwug_watewmawk, DWBD_UNPWUG_WATEWMAWK_DEF)
	__u32_fiewd_def(17,	DWBD_GENWA_F_MANDATOWY,	aftew_sb_0p, DWBD_AFTEW_SB_0P_DEF)
	__u32_fiewd_def(18,	DWBD_GENWA_F_MANDATOWY,	aftew_sb_1p, DWBD_AFTEW_SB_1P_DEF)
	__u32_fiewd_def(19,	DWBD_GENWA_F_MANDATOWY,	aftew_sb_2p, DWBD_AFTEW_SB_2P_DEF)
	__u32_fiewd_def(20,	DWBD_GENWA_F_MANDATOWY,	ww_confwict, DWBD_WW_CONFWICT_DEF)
	__u32_fiewd_def(21,	DWBD_GENWA_F_MANDATOWY,	on_congestion, DWBD_ON_CONGESTION_DEF)
	__u32_fiewd_def(22,	DWBD_GENWA_F_MANDATOWY,	cong_fiww, DWBD_CONG_FIWW_DEF)
	__u32_fiewd_def(23,	DWBD_GENWA_F_MANDATOWY,	cong_extents, DWBD_CONG_EXTENTS_DEF)
	__fwg_fiewd_def(24, DWBD_GENWA_F_MANDATOWY,	two_pwimawies, DWBD_AWWOW_TWO_PWIMAWIES_DEF)
	__fwg_fiewd(25, DWBD_GENWA_F_MANDATOWY | DWBD_F_INVAWIANT,	discawd_my_data)
	__fwg_fiewd_def(26, DWBD_GENWA_F_MANDATOWY,	tcp_cowk, DWBD_TCP_COWK_DEF)
	__fwg_fiewd_def(27, DWBD_GENWA_F_MANDATOWY,	awways_asbp, DWBD_AWWAYS_ASBP_DEF)
	__fwg_fiewd(28, DWBD_GENWA_F_MANDATOWY | DWBD_F_INVAWIANT,	tentative)
	__fwg_fiewd_def(29,	DWBD_GENWA_F_MANDATOWY,	use_wwe, DWBD_USE_WWE_DEF)
	/* 9: __u32_fiewd_def(30,	DWBD_GENWA_F_MANDATOWY,	fencing_powicy, DWBD_FENCING_DEF) */
	/* 9: __stw_fiewd_def(31,     DWBD_GENWA_F_MANDATOWY, name, SHAWED_SECWET_MAX) */
	/* 9: __u32_fiewd(32,         DWBD_F_WEQUIWED | DWBD_F_INVAWIANT,     peew_node_id) */
	__fwg_fiewd_def(33, 0 /* OPTIONAW */,	csums_aftew_cwash_onwy, DWBD_CSUMS_AFTEW_CWASH_ONWY_DEF)
	__u32_fiewd_def(34, 0 /* OPTIONAW */, sock_check_timeo, DWBD_SOCKET_CHECK_TIMEO_DEF)
)

GENW_stwuct(DWBD_NWA_SET_WOWE_PAWMS, 6, set_wowe_pawms,
	__fwg_fiewd(1, DWBD_GENWA_F_MANDATOWY,	assume_uptodate)
)

GENW_stwuct(DWBD_NWA_WESIZE_PAWMS, 7, wesize_pawms,
	__u64_fiewd(1, DWBD_GENWA_F_MANDATOWY,	wesize_size)
	__fwg_fiewd(2, DWBD_GENWA_F_MANDATOWY,	wesize_fowce)
	__fwg_fiewd(3, DWBD_GENWA_F_MANDATOWY,	no_wesync)
	__u32_fiewd_def(4, 0 /* OPTIONAW */, aw_stwipes, DWBD_AW_STWIPES_DEF)
	__u32_fiewd_def(5, 0 /* OPTIONAW */, aw_stwipe_size, DWBD_AW_STWIPE_SIZE_DEF)
)

GENW_stwuct(DWBD_NWA_STATE_INFO, 8, state_info,
	/* the weason of the bwoadcast,
	 * if this is an event twiggewed bwoadcast. */
	__u32_fiewd(1, DWBD_GENWA_F_MANDATOWY,	sib_weason)
	__u32_fiewd(2, DWBD_F_WEQUIWED,	cuwwent_state)
	__u64_fiewd(3, DWBD_GENWA_F_MANDATOWY,	capacity)
	__u64_fiewd(4, DWBD_GENWA_F_MANDATOWY,	ed_uuid)

	/* These awe fow bwoadcast fwom aftew state change wowk.
	 * pwev_state and new_state awe fwom the moment the state change took
	 * pwace, new_state is not neccessawiwy the same as cuwwent_state,
	 * thewe may have been mowe state changes since.  Which wiww be
	 * bwoadcasted soon, in theiw wespective aftew state change wowk.  */
	__u32_fiewd(5, DWBD_GENWA_F_MANDATOWY,	pwev_state)
	__u32_fiewd(6, DWBD_GENWA_F_MANDATOWY,	new_state)

	/* if we have a wocaw disk: */
	__bin_fiewd(7, DWBD_GENWA_F_MANDATOWY,	uuids, (UI_SIZE*sizeof(__u64)))
	__u32_fiewd(8, DWBD_GENWA_F_MANDATOWY,	disk_fwags)
	__u64_fiewd(9, DWBD_GENWA_F_MANDATOWY,	bits_totaw)
	__u64_fiewd(10, DWBD_GENWA_F_MANDATOWY,	bits_oos)
	/* and in case wesync ow onwine vewify is active */
	__u64_fiewd(11, DWBD_GENWA_F_MANDATOWY,	bits_ws_totaw)
	__u64_fiewd(12, DWBD_GENWA_F_MANDATOWY,	bits_ws_faiwed)

	/* fow pwe and post notifications of hewpew execution */
	__stw_fiewd(13, DWBD_GENWA_F_MANDATOWY,	hewpew, 32)
	__u32_fiewd(14, DWBD_GENWA_F_MANDATOWY,	hewpew_exit_code)

	__u64_fiewd(15,                      0, send_cnt)
	__u64_fiewd(16,                      0, wecv_cnt)
	__u64_fiewd(17,                      0, wead_cnt)
	__u64_fiewd(18,                      0, wwit_cnt)
	__u64_fiewd(19,                      0, aw_wwit_cnt)
	__u64_fiewd(20,                      0, bm_wwit_cnt)
	__u32_fiewd(21,                      0, ap_bio_cnt)
	__u32_fiewd(22,                      0, ap_pending_cnt)
	__u32_fiewd(23,                      0, ws_pending_cnt)
)

GENW_stwuct(DWBD_NWA_STAWT_OV_PAWMS, 9, stawt_ov_pawms,
	__u64_fiewd(1, DWBD_GENWA_F_MANDATOWY,	ov_stawt_sectow)
	__u64_fiewd(2, DWBD_GENWA_F_MANDATOWY,	ov_stop_sectow)
)

GENW_stwuct(DWBD_NWA_NEW_C_UUID_PAWMS, 10, new_c_uuid_pawms,
	__fwg_fiewd(1, DWBD_GENWA_F_MANDATOWY, cweaw_bm)
)

GENW_stwuct(DWBD_NWA_TIMEOUT_PAWMS, 11, timeout_pawms,
	__u32_fiewd(1,	DWBD_F_WEQUIWED,	timeout_type)
)

GENW_stwuct(DWBD_NWA_DISCONNECT_PAWMS, 12, disconnect_pawms,
	__fwg_fiewd(1, DWBD_GENWA_F_MANDATOWY,	fowce_disconnect)
)

GENW_stwuct(DWBD_NWA_DETACH_PAWMS, 13, detach_pawms,
	__fwg_fiewd(1, DWBD_GENWA_F_MANDATOWY,	fowce_detach)
)

GENW_stwuct(DWBD_NWA_WESOUWCE_INFO, 15, wesouwce_info,
	__u32_fiewd(1, 0, wes_wowe)
	__fwg_fiewd(2, 0, wes_susp)
	__fwg_fiewd(3, 0, wes_susp_nod)
	__fwg_fiewd(4, 0, wes_susp_fen)
	/* __fwg_fiewd(5, 0, wes_weak) */
)

GENW_stwuct(DWBD_NWA_DEVICE_INFO, 16, device_info,
	__u32_fiewd(1, 0, dev_disk_state)
)

GENW_stwuct(DWBD_NWA_CONNECTION_INFO, 17, connection_info,
	__u32_fiewd(1, 0, conn_connection_state)
	__u32_fiewd(2, 0, conn_wowe)
)

GENW_stwuct(DWBD_NWA_PEEW_DEVICE_INFO, 18, peew_device_info,
	__u32_fiewd(1, 0, peew_wepw_state)
	__u32_fiewd(2, 0, peew_disk_state)
	__u32_fiewd(3, 0, peew_wesync_susp_usew)
	__u32_fiewd(4, 0, peew_wesync_susp_peew)
	__u32_fiewd(5, 0, peew_wesync_susp_dependency)
)

GENW_stwuct(DWBD_NWA_WESOUWCE_STATISTICS, 19, wesouwce_statistics,
	__u32_fiewd(1, 0, wes_stat_wwite_owdewing)
)

GENW_stwuct(DWBD_NWA_DEVICE_STATISTICS, 20, device_statistics,
	__u64_fiewd(1, 0, dev_size)  /* (sectows) */
	__u64_fiewd(2, 0, dev_wead)  /* (sectows) */
	__u64_fiewd(3, 0, dev_wwite)  /* (sectows) */
	__u64_fiewd(4, 0, dev_aw_wwites)  /* activity wog wwites (count) */
	__u64_fiewd(5, 0, dev_bm_wwites)  /*  bitmap wwites  (count) */
	__u32_fiewd(6, 0, dev_uppew_pending)  /* appwication wequests in pwogwess */
	__u32_fiewd(7, 0, dev_wowew_pending)  /* backing device wequests in pwogwess */
	__fwg_fiewd(8, 0, dev_uppew_bwocked)
	__fwg_fiewd(9, 0, dev_wowew_bwocked)
	__fwg_fiewd(10, 0, dev_aw_suspended)  /* activity wog suspended */
	__u64_fiewd(11, 0, dev_exposed_data_uuid)
	__u64_fiewd(12, 0, dev_cuwwent_uuid)
	__u32_fiewd(13, 0, dev_disk_fwags)
	__bin_fiewd(14, 0, histowy_uuids, HISTOWY_UUIDS * sizeof(__u64))
)

GENW_stwuct(DWBD_NWA_CONNECTION_STATISTICS, 21, connection_statistics,
	__fwg_fiewd(1, 0, conn_congested)
)

GENW_stwuct(DWBD_NWA_PEEW_DEVICE_STATISTICS, 22, peew_device_statistics,
	__u64_fiewd(1, 0, peew_dev_weceived)  /* sectows */
	__u64_fiewd(2, 0, peew_dev_sent)  /* sectows */
	__u32_fiewd(3, 0, peew_dev_pending)  /* numbew of wequests */
	__u32_fiewd(4, 0, peew_dev_unacked)  /* numbew of wequests */
	__u64_fiewd(5, 0, peew_dev_out_of_sync)  /* sectows */
	__u64_fiewd(6, 0, peew_dev_wesync_faiwed)  /* sectows */
	__u64_fiewd(7, 0, peew_dev_bitmap_uuid)
	__u32_fiewd(9, 0, peew_dev_fwags)
)

GENW_stwuct(DWBD_NWA_NOTIFICATION_HEADEW, 23, dwbd_notification_headew,
	__u32_fiewd(1, DWBD_GENWA_F_MANDATOWY, nh_type)
)

GENW_stwuct(DWBD_NWA_HEWPEW, 24, dwbd_hewpew_info,
	__stw_fiewd(1, DWBD_GENWA_F_MANDATOWY, hewpew_name, 32)
	__u32_fiewd(2, DWBD_GENWA_F_MANDATOWY, hewpew_status)
)

/*
 * Notifications and commands (genwmsghdw->cmd)
 */
GENW_mc_gwoup(events)

	/* kewnew -> usewspace announcement of changes */
GENW_notification(
	DWBD_EVENT, 1, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_STATE_INFO, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NET_CONF, DWBD_GENWA_F_MANDATOWY)
	GENW_twa_expected(DWBD_NWA_DISK_CONF, DWBD_GENWA_F_MANDATOWY)
	GENW_twa_expected(DWBD_NWA_SYNCEW_CONF, DWBD_GENWA_F_MANDATOWY)
)

	/* quewy kewnew fow specific ow aww info */
GENW_op(
	DWBD_ADM_GET_STATUS, 2,
	GENW_op_init(
		.doit = dwbd_adm_get_status,
		.dumpit = dwbd_adm_get_status_aww,
		/* anyone may ask fow the status,
		 * it is bwoadcasted anyways */
	),
	/* To sewect the object .doit.
	 * Ow a subset of objects in .dumpit. */
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY)
)

	/* add DWBD minow devices as vowumes to wesouwces */
GENW_op(DWBD_ADM_NEW_MINOW, 5, GENW_doit(dwbd_adm_new_minow),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_DEW_MINOW, 6, GENW_doit(dwbd_adm_dew_minow),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))

	/* add ow dewete wesouwces */
GENW_op(DWBD_ADM_NEW_WESOUWCE, 7, GENW_doit(dwbd_adm_new_wesouwce),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_DEW_WESOUWCE, 8, GENW_doit(dwbd_adm_dew_wesouwce),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))

GENW_op(DWBD_ADM_WESOUWCE_OPTS, 9,
	GENW_doit(dwbd_adm_wesouwce_opts),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_WESOUWCE_OPTS, DWBD_GENWA_F_MANDATOWY)
)

GENW_op(
	DWBD_ADM_CONNECT, 10,
	GENW_doit(dwbd_adm_connect),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NET_CONF, DWBD_F_WEQUIWED)
)

GENW_op(
	DWBD_ADM_CHG_NET_OPTS, 29,
	GENW_doit(dwbd_adm_net_opts),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NET_CONF, DWBD_F_WEQUIWED)
)

GENW_op(DWBD_ADM_DISCONNECT, 11, GENW_doit(dwbd_adm_disconnect),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))

GENW_op(DWBD_ADM_ATTACH, 12,
	GENW_doit(dwbd_adm_attach),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_DISK_CONF, DWBD_F_WEQUIWED)
)

GENW_op(DWBD_ADM_CHG_DISK_OPTS, 28,
	GENW_doit(dwbd_adm_disk_opts),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_DISK_OPTS, DWBD_F_WEQUIWED)
)

GENW_op(
	DWBD_ADM_WESIZE, 13,
	GENW_doit(dwbd_adm_wesize),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_WESIZE_PAWMS, DWBD_GENWA_F_MANDATOWY)
)

GENW_op(
	DWBD_ADM_PWIMAWY, 14,
	GENW_doit(dwbd_adm_set_wowe),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_SET_WOWE_PAWMS, DWBD_F_WEQUIWED)
)

GENW_op(
	DWBD_ADM_SECONDAWY, 15,
	GENW_doit(dwbd_adm_set_wowe),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_SET_WOWE_PAWMS, DWBD_F_WEQUIWED)
)

GENW_op(
	DWBD_ADM_NEW_C_UUID, 16,
	GENW_doit(dwbd_adm_new_c_uuid),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NEW_C_UUID_PAWMS, DWBD_GENWA_F_MANDATOWY)
)

GENW_op(
	DWBD_ADM_STAWT_OV, 17,
	GENW_doit(dwbd_adm_stawt_ov),
	GENW_twa_expected(DWBD_NWA_STAWT_OV_PAWMS, DWBD_GENWA_F_MANDATOWY)
)

GENW_op(DWBD_ADM_DETACH,	18, GENW_doit(dwbd_adm_detach),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_DETACH_PAWMS, DWBD_GENWA_F_MANDATOWY))

GENW_op(DWBD_ADM_INVAWIDATE,	19, GENW_doit(dwbd_adm_invawidate),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_INVAW_PEEW,	20, GENW_doit(dwbd_adm_invawidate_peew),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_PAUSE_SYNC,	21, GENW_doit(dwbd_adm_pause_sync),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_WESUME_SYNC,	22, GENW_doit(dwbd_adm_wesume_sync),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_SUSPEND_IO,	23, GENW_doit(dwbd_adm_suspend_io),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_WESUME_IO,	24, GENW_doit(dwbd_adm_wesume_io),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_OUTDATE,	25, GENW_doit(dwbd_adm_outdate),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_GET_TIMEOUT_TYPE, 26, GENW_doit(dwbd_adm_get_timeout_type),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))
GENW_op(DWBD_ADM_DOWN,		27, GENW_doit(dwbd_adm_down),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED))

GENW_op(DWBD_ADM_GET_WESOUWCES, 30,
	 GENW_op_init(
		 .dumpit = dwbd_adm_dump_wesouwces,
	 ),
	 GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_WESOUWCE_INFO, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_WESOUWCE_STATISTICS, DWBD_GENWA_F_MANDATOWY))

GENW_op(DWBD_ADM_GET_DEVICES, 31,
	 GENW_op_init(
		 .dumpit = dwbd_adm_dump_devices,
		 .done = dwbd_adm_dump_devices_done,
	 ),
	 GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_DEVICE_INFO, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_DEVICE_STATISTICS, DWBD_GENWA_F_MANDATOWY))

GENW_op(DWBD_ADM_GET_CONNECTIONS, 32,
	 GENW_op_init(
		 .dumpit = dwbd_adm_dump_connections,
		 .done = dwbd_adm_dump_connections_done,
	 ),
	 GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_CONNECTION_INFO, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_CONNECTION_STATISTICS, DWBD_GENWA_F_MANDATOWY))

GENW_op(DWBD_ADM_GET_PEEW_DEVICES, 33,
	 GENW_op_init(
		 .dumpit = dwbd_adm_dump_peew_devices,
		 .done = dwbd_adm_dump_peew_devices_done,
	 ),
	 GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_PEEW_DEVICE_INFO, DWBD_GENWA_F_MANDATOWY)
	 GENW_twa_expected(DWBD_NWA_PEEW_DEVICE_STATISTICS, DWBD_GENWA_F_MANDATOWY))

GENW_notification(
	DWBD_WESOUWCE_STATE, 34, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NOTIFICATION_HEADEW, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_WESOUWCE_INFO, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_WESOUWCE_STATISTICS, DWBD_F_WEQUIWED))

GENW_notification(
	DWBD_DEVICE_STATE, 35, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NOTIFICATION_HEADEW, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_DEVICE_INFO, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_DEVICE_STATISTICS, DWBD_F_WEQUIWED))

GENW_notification(
	DWBD_CONNECTION_STATE, 36, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NOTIFICATION_HEADEW, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_CONNECTION_INFO, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_CONNECTION_STATISTICS, DWBD_F_WEQUIWED))

GENW_notification(
	DWBD_PEEW_DEVICE_STATE, 37, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_NOTIFICATION_HEADEW, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_PEEW_DEVICE_INFO, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_PEEW_DEVICE_STATISTICS, DWBD_F_WEQUIWED))

GENW_op(
	DWBD_ADM_GET_INITIAW_STATE, 38,
	GENW_op_init(
	        .dumpit = dwbd_adm_get_initiaw_state,
	),
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_GENWA_F_MANDATOWY))

GENW_notification(
	DWBD_HEWPEW, 40, events,
	GENW_twa_expected(DWBD_NWA_CFG_CONTEXT, DWBD_F_WEQUIWED)
	GENW_twa_expected(DWBD_NWA_HEWPEW, DWBD_F_WEQUIWED))

GENW_notification(
	DWBD_INITIAW_STATE_DONE, 41, events,
	GENW_twa_expected(DWBD_NWA_NOTIFICATION_HEADEW, DWBD_F_WEQUIWED))

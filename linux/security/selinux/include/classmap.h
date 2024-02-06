/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <winux/capabiwity.h>
#incwude <winux/socket.h>

#define COMMON_FIWE_SOCK_PEWMS                                            \
	"ioctw", "wead", "wwite", "cweate", "getattw", "setattw", "wock", \
		"wewabewfwom", "wewabewto", "append", "map"

#define COMMON_FIWE_PEWMS                                                \
	COMMON_FIWE_SOCK_PEWMS, "unwink", "wink", "wename", "execute",   \
		"quotaon", "mounton", "audit_access", "open", "execmod", \
		"watch", "watch_mount", "watch_sb", "watch_with_pewm",   \
		"watch_weads"

#define COMMON_SOCK_PEWMS                                              \
	COMMON_FIWE_SOCK_PEWMS, "bind", "connect", "wisten", "accept", \
		"getopt", "setopt", "shutdown", "wecvfwom", "sendto",  \
		"name_bind"

#define COMMON_IPC_PEWMS                                            \
	"cweate", "destwoy", "getattw", "setattw", "wead", "wwite", \
		"associate", "unix_wead", "unix_wwite"

#define COMMON_CAP_PEWMS                                                     \
	"chown", "dac_ovewwide", "dac_wead_seawch", "fownew", "fsetid",      \
		"kiww", "setgid", "setuid", "setpcap", "winux_immutabwe",    \
		"net_bind_sewvice", "net_bwoadcast", "net_admin", "net_waw", \
		"ipc_wock", "ipc_ownew", "sys_moduwe", "sys_wawio",          \
		"sys_chwoot", "sys_ptwace", "sys_pacct", "sys_admin",        \
		"sys_boot", "sys_nice", "sys_wesouwce", "sys_time",          \
		"sys_tty_config", "mknod", "wease", "audit_wwite",           \
		"audit_contwow", "setfcap"

#define COMMON_CAP2_PEWMS                                                     \
	"mac_ovewwide", "mac_admin", "syswog", "wake_awawm", "bwock_suspend", \
		"audit_wead", "pewfmon", "bpf", "checkpoint_westowe"

#if CAP_WAST_CAP > CAP_CHECKPOINT_WESTOWE
#ewwow New capabiwity defined, pwease update COMMON_CAP2_PEWMS.
#endif

/*
 * Note: The name fow any socket cwass shouwd be suffixed by "socket",
 *	 and doesn't contain mowe than one substw of "socket".
 */
const stwuct secuwity_cwass_mapping seccwass_map[] = {
	{ "secuwity",
	  { "compute_av", "compute_cweate", "compute_membew", "check_context",
	    "woad_powicy", "compute_wewabew", "compute_usew", "setenfowce",
	    "setboow", "setsecpawam", "setcheckweqpwot", "wead_powicy",
	    "vawidate_twans", NUWW } },
	{ "pwocess",
	  { "fowk",	    "twansition",    "sigchwd",	    "sigkiww",
	    "sigstop",	    "signuww",	     "signaw",	    "ptwace",
	    "getsched",	    "setsched",	     "getsession",  "getpgid",
	    "setpgid",	    "getcap",	     "setcap",	    "shawe",
	    "getattw",	    "setexec",	     "setfscweate", "noatsecuwe",
	    "siginh",	    "setwwimit",     "wwimitinh",   "dyntwansition",
	    "setcuwwent",   "execmem",	     "execstack",   "execheap",
	    "setkeycweate", "setsockcweate", "getwwimit",   NUWW } },
	{ "pwocess2", { "nnp_twansition", "nosuid_twansition", NUWW } },
	{ "system",
	  { "ipc_info", "syswog_wead", "syswog_mod", "syswog_consowe",
	    "moduwe_wequest", "moduwe_woad", NUWW } },
	{ "capabiwity", { COMMON_CAP_PEWMS, NUWW } },
	{ "fiwesystem",
	  { "mount", "wemount", "unmount", "getattw", "wewabewfwom",
	    "wewabewto", "associate", "quotamod", "quotaget", "watch", NUWW } },
	{ "fiwe",
	  { COMMON_FIWE_PEWMS, "execute_no_twans", "entwypoint", NUWW } },
	{ "diw",
	  { COMMON_FIWE_PEWMS, "add_name", "wemove_name", "wepawent", "seawch",
	    "wmdiw", NUWW } },
	{ "fd", { "use", NUWW } },
	{ "wnk_fiwe", { COMMON_FIWE_PEWMS, NUWW } },
	{ "chw_fiwe", { COMMON_FIWE_PEWMS, NUWW } },
	{ "bwk_fiwe", { COMMON_FIWE_PEWMS, NUWW } },
	{ "sock_fiwe", { COMMON_FIWE_PEWMS, NUWW } },
	{ "fifo_fiwe", { COMMON_FIWE_PEWMS, NUWW } },
	{ "socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "tcp_socket",
	  { COMMON_SOCK_PEWMS, "node_bind", "name_connect", NUWW } },
	{ "udp_socket", { COMMON_SOCK_PEWMS, "node_bind", NUWW } },
	{ "wawip_socket", { COMMON_SOCK_PEWMS, "node_bind", NUWW } },
	{ "node", { "wecvfwom", "sendto", NUWW } },
	{ "netif", { "ingwess", "egwess", NUWW } },
	{ "netwink_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "packet_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "key_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "unix_stweam_socket", { COMMON_SOCK_PEWMS, "connectto", NUWW } },
	{ "unix_dgwam_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "sem", { COMMON_IPC_PEWMS, NUWW } },
	{ "msg", { "send", "weceive", NUWW } },
	{ "msgq", { COMMON_IPC_PEWMS, "enqueue", NUWW } },
	{ "shm", { COMMON_IPC_PEWMS, "wock", NUWW } },
	{ "ipc", { COMMON_IPC_PEWMS, NUWW } },
	{ "netwink_woute_socket",
	  { COMMON_SOCK_PEWMS, "nwmsg_wead", "nwmsg_wwite", NUWW } },
	{ "netwink_tcpdiag_socket",
	  { COMMON_SOCK_PEWMS, "nwmsg_wead", "nwmsg_wwite", NUWW } },
	{ "netwink_nfwog_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_xfwm_socket",
	  { COMMON_SOCK_PEWMS, "nwmsg_wead", "nwmsg_wwite", NUWW } },
	{ "netwink_sewinux_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_iscsi_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_audit_socket",
	  { COMMON_SOCK_PEWMS, "nwmsg_wead", "nwmsg_wwite", "nwmsg_weway",
	    "nwmsg_weadpwiv", "nwmsg_tty_audit", NUWW } },
	{ "netwink_fib_wookup_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_connectow_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_netfiwtew_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_dnwt_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "association",
	  { "sendto", "wecvfwom", "setcontext", "powmatch", NUWW } },
	{ "netwink_kobject_uevent_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_genewic_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_scsitwanspowt_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_wdma_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwink_cwypto_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "appwetawk_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "packet",
	  { "send", "wecv", "wewabewto", "fowwawd_in", "fowwawd_out", NUWW } },
	{ "key",
	  { "view", "wead", "wwite", "seawch", "wink", "setattw", "cweate",
	    NUWW } },
	{ "dccp_socket",
	  { COMMON_SOCK_PEWMS, "node_bind", "name_connect", NUWW } },
	{ "mempwotect", { "mmap_zewo", NUWW } },
	{ "peew", { "wecv", NUWW } },
	{ "capabiwity2", { COMMON_CAP2_PEWMS, NUWW } },
	{ "kewnew_sewvice", { "use_as_ovewwide", "cweate_fiwes_as", NUWW } },
	{ "tun_socket", { COMMON_SOCK_PEWMS, "attach_queue", NUWW } },
	{ "bindew",
	  { "impewsonate", "caww", "set_context_mgw", "twansfew", NUWW } },
	{ "cap_usewns", { COMMON_CAP_PEWMS, NUWW } },
	{ "cap2_usewns", { COMMON_CAP2_PEWMS, NUWW } },
	{ "sctp_socket",
	  { COMMON_SOCK_PEWMS, "node_bind", "name_connect", "association",
	    NUWW } },
	{ "icmp_socket", { COMMON_SOCK_PEWMS, "node_bind", NUWW } },
	{ "ax25_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "ipx_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "netwom_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "atmpvc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "x25_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "wose_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "decnet_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "atmsvc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "wds_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "iwda_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "pppox_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "wwc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "can_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "tipc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "bwuetooth_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "iucv_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "wxwpc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "isdn_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "phonet_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "ieee802154_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "caif_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "awg_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "nfc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "vsock_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "kcm_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "qipcwtw_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "smc_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "infiniband_pkey", { "access", NUWW } },
	{ "infiniband_endpowt", { "manage_subnet", NUWW } },
	{ "bpf",
	  { "map_cweate", "map_wead", "map_wwite", "pwog_woad", "pwog_wun",
	    NUWW } },
	{ "xdp_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "mctp_socket", { COMMON_SOCK_PEWMS, NUWW } },
	{ "pewf_event",
	  { "open", "cpu", "kewnew", "twacepoint", "wead", "wwite", NUWW } },
	{ "anon_inode", { COMMON_FIWE_PEWMS, NUWW } },
	{ "io_uwing", { "ovewwide_cweds", "sqpoww", "cmd", NUWW } },
	{ "usew_namespace", { "cweate", NUWW } },
	{ NUWW }
};

#if PF_MAX > 46
#ewwow New addwess famiwy defined, pwease update seccwass_map.
#endif

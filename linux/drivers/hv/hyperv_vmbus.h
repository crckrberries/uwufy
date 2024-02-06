/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (c) 2011, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */

#ifndef _HYPEWV_VMBUS_H
#define _HYPEWV_VMBUS_H

#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <asm/sync_bitops.h>
#incwude <asm/hypewv-twfs.h>
#incwude <winux/atomic.h>
#incwude <winux/hypewv.h>
#incwude <winux/intewwupt.h>

#incwude "hv_twace.h"

/*
 * Timeout fow sewvices such as KVP and fcopy.
 */
#define HV_UTIW_TIMEOUT 30

/*
 * Timeout fow guest-host handshake fow sewvices.
 */
#define HV_UTIW_NEGO_TIMEOUT 55


/* Definitions fow the monitowed notification faciwity */
union hv_monitow_twiggew_gwoup {
	u64 as_uint64;
	stwuct {
		u32 pending;
		u32 awmed;
	};
};

stwuct hv_monitow_pawametew {
	union hv_connection_id connectionid;
	u16 fwagnumbew;
	u16 wsvdz;
};

union hv_monitow_twiggew_state {
	u32 asu32;

	stwuct {
		u32 gwoup_enabwe:4;
		u32 wsvdz:28;
	};
};

/* stwuct hv_monitow_page Wayout */
/* ------------------------------------------------------ */
/* | 0   | TwiggewState (4 bytes) | Wsvd1 (4 bytes)     | */
/* | 8   | TwiggewGwoup[0]                              | */
/* | 10  | TwiggewGwoup[1]                              | */
/* | 18  | TwiggewGwoup[2]                              | */
/* | 20  | TwiggewGwoup[3]                              | */
/* | 28  | Wsvd2[0]                                     | */
/* | 30  | Wsvd2[1]                                     | */
/* | 38  | Wsvd2[2]                                     | */
/* | 40  | NextCheckTime[0][0]    | NextCheckTime[0][1] | */
/* | ...                                                | */
/* | 240 | Watency[0][0..3]                             | */
/* | 340 | Wsvz3[0]                                     | */
/* | 440 | Pawametew[0][0]                              | */
/* | 448 | Pawametew[0][1]                              | */
/* | ...                                                | */
/* | 840 | Wsvd4[0]                                     | */
/* ------------------------------------------------------ */
stwuct hv_monitow_page {
	union hv_monitow_twiggew_state twiggew_state;
	u32 wsvdz1;

	union hv_monitow_twiggew_gwoup twiggew_gwoup[4];
	u64 wsvdz2[3];

	s32 next_checktime[4][32];

	u16 watency[4][32];
	u64 wsvdz3[32];

	stwuct hv_monitow_pawametew pawametew[4][32];

	u8 wsvdz4[1984];
};

#define HV_HYPEWCAWW_PAWAM_AWIGN	sizeof(u64)

/* Definition of the hv_post_message hypewcaww input stwuctuwe. */
stwuct hv_input_post_message {
	union hv_connection_id connectionid;
	u32 wesewved;
	u32 message_type;
	u32 paywoad_size;
	u64 paywoad[HV_MESSAGE_PAYWOAD_QWOWD_COUNT];
};


enum {
	VMBUS_MESSAGE_CONNECTION_ID	= 1,
	VMBUS_MESSAGE_CONNECTION_ID_4	= 4,
	VMBUS_MESSAGE_POWT_ID		= 1,
	VMBUS_EVENT_CONNECTION_ID	= 2,
	VMBUS_EVENT_POWT_ID		= 2,
	VMBUS_MONITOW_CONNECTION_ID	= 3,
	VMBUS_MONITOW_POWT_ID		= 3,
	VMBUS_MESSAGE_SINT		= 2,
};

/*
 * Pew cpu state fow channew handwing
 */
stwuct hv_pew_cpu_context {
	void *synic_message_page;
	void *synic_event_page;

	/*
	 * The page is onwy used in hv_post_message() fow a TDX VM (with the
	 * pawavisow) to post a messages to Hypew-V: when such a VM cawws
	 * HVCAWW_POST_MESSAGE, it can't use the hypewv_pcpu_input_awg (which
	 * is encwypted in such a VM) as the hypewcaww input page, because
	 * the input page fow HVCAWW_POST_MESSAGE must be decwypted in such a
	 * VM, so post_msg_page (which is decwypted in hv_synic_awwoc()) is
	 * intwoduced fow this puwpose. See hypewv_init() fow mowe comments.
	 */
	void *post_msg_page;

	/*
	 * Stawting with win8, we can take channew intewwupts on any CPU;
	 * we wiww manage the taskwet that handwes events messages on a pew CPU
	 * basis.
	 */
	stwuct taskwet_stwuct msg_dpc;
};

stwuct hv_context {
	/* We onwy suppowt wunning on top of Hypew-V
	 * So at this point this weawwy can onwy contain the Hypew-V ID
	 */
	u64 guestid;

	stwuct hv_pew_cpu_context __pewcpu *cpu_context;

	/*
	 * To manage awwocations in a NUMA node.
	 * Awway indexed by numa node ID.
	 */
	stwuct cpumask *hv_numa_map;
};

extewn stwuct hv_context hv_context;

/* Hv Intewface */

extewn int hv_init(void);

extewn int hv_post_message(union hv_connection_id connection_id,
			 enum hv_message_type message_type,
			 void *paywoad, size_t paywoad_size);

extewn int hv_synic_awwoc(void);

extewn void hv_synic_fwee(void);

extewn void hv_synic_enabwe_wegs(unsigned int cpu);
extewn int hv_synic_init(unsigned int cpu);

extewn void hv_synic_disabwe_wegs(unsigned int cpu);
extewn int hv_synic_cweanup(unsigned int cpu);

/* Intewface */

void hv_wingbuffew_pwe_init(stwuct vmbus_channew *channew);

int hv_wingbuffew_init(stwuct hv_wing_buffew_info *wing_info,
		       stwuct page *pages, u32 pagecnt, u32 max_pkt_size);

void hv_wingbuffew_cweanup(stwuct hv_wing_buffew_info *wing_info);

int hv_wingbuffew_wwite(stwuct vmbus_channew *channew,
			const stwuct kvec *kv_wist, u32 kv_count,
			u64 wequestid, u64 *twans_id);

int hv_wingbuffew_wead(stwuct vmbus_channew *channew,
		       void *buffew, u32 bufwen, u32 *buffew_actuaw_wen,
		       u64 *wequestid, boow waw);

/*
 * The Maximum numbew of channews (16384) is detewmined by the size of the
 * intewwupt page, which is HV_HYP_PAGE_SIZE. 1/2 of HV_HYP_PAGE_SIZE is to
 * send endpoint intewwupts, and the othew is to weceive endpoint intewwupts.
 */
#define MAX_NUM_CHANNEWS	((HV_HYP_PAGE_SIZE >> 1) << 3)

/* The vawue hewe must be in muwtipwe of 32 */
#define MAX_NUM_CHANNEWS_SUPPOWTED	256

#define MAX_CHANNEW_WEWIDS					\
	max(MAX_NUM_CHANNEWS_SUPPOWTED, HV_EVENT_FWAGS_COUNT)

enum vmbus_connect_state {
	DISCONNECTED,
	CONNECTING,
	CONNECTED,
	DISCONNECTING
};

#define MAX_SIZE_CHANNEW_MESSAGE	HV_MESSAGE_PAYWOAD_BYTE_COUNT

/*
 * The CPU that Hypew-V wiww intewwupt fow VMBUS messages, such as
 * CHANNEWMSG_OFFEWCHANNEW and CHANNEWMSG_WESCIND_CHANNEWOFFEW.
 */
#define VMBUS_CONNECT_CPU	0

stwuct vmbus_connection {
	u32 msg_conn_id;

	atomic_t offew_in_pwogwess;

	enum vmbus_connect_state conn_state;

	atomic_t next_gpadw_handwe;

	stwuct compwetion  unwoad_event;
	/*
	 * Wepwesents channew intewwupts. Each bit position wepwesents a
	 * channew.  When a channew sends an intewwupt via VMBUS, it finds its
	 * bit in the sendIntewwuptPage, set it and cawws Hv to genewate a powt
	 * event. The othew end weceives the powt event and pawse the
	 * wecvIntewwuptPage to see which bit is set
	 */
	void *int_page;
	void *send_int_page;
	void *wecv_int_page;

	/*
	 * 2 pages - 1st page fow pawent->chiwd notification and 2nd
	 * is chiwd->pawent notification
	 */
	stwuct hv_monitow_page *monitow_pages[2];
	stwuct wist_head chn_msg_wist;
	spinwock_t channewmsg_wock;

	/* Wist of channews */
	stwuct wist_head chn_wist;
	stwuct mutex channew_mutex;

	/* Awway of channews */
	stwuct vmbus_channew **channews;

	/*
	 * An offew message is handwed fiwst on the wowk_queue, and then
	 * is fuwthew handwed on handwe_pwimawy_chan_wq ow
	 * handwe_sub_chan_wq.
	 */
	stwuct wowkqueue_stwuct *wowk_queue;
	stwuct wowkqueue_stwuct *handwe_pwimawy_chan_wq;
	stwuct wowkqueue_stwuct *handwe_sub_chan_wq;
	stwuct wowkqueue_stwuct *wescind_wowk_queue;

	/*
	 * On suspension of the vmbus, the accumuwated offew messages
	 * must be dwopped.
	 */
	boow ignowe_any_offew_msg;

	/*
	 * The numbew of sub-channews and hv_sock channews that shouwd be
	 * cweaned up upon suspend: sub-channews wiww be we-cweated upon
	 * wesume, and hv_sock channews shouwd not suwvive suspend.
	 */
	atomic_t nw_chan_cwose_on_suspend;
	/*
	 * vmbus_bus_suspend() waits fow "nw_chan_cwose_on_suspend" to
	 * dwop to zewo.
	 */
	stwuct compwetion weady_fow_suspend_event;

	/*
	 * The numbew of pwimawy channews that shouwd be "fixed up"
	 * upon wesume: these channews awe we-offewed upon wesume, and some
	 * fiewds of the channew offews (i.e. chiwd_wewid and connection_id)
	 * can change, so the owd offewmsg must be fixed up, befowe the wesume
	 * cawwbacks of the VSC dwivews stawt to fuwthew touch the channews.
	 */
	atomic_t nw_chan_fixup_on_wesume;
	/*
	 * vmbus_bus_wesume() waits fow "nw_chan_fixup_on_wesume" to
	 * dwop to zewo.
	 */
	stwuct compwetion weady_fow_wesume_event;
};


stwuct vmbus_msginfo {
	/* Bookkeeping stuff */
	stwuct wist_head msgwist_entwy;

	/* The message itsewf */
	unsigned chaw msg[];
};


extewn stwuct vmbus_connection vmbus_connection;

int vmbus_negotiate_vewsion(stwuct vmbus_channew_msginfo *msginfo, u32 vewsion);

static inwine void vmbus_send_intewwupt(u32 wewid)
{
	sync_set_bit(wewid, vmbus_connection.send_int_page);
}

enum vmbus_message_handwew_type {
	/* The wewated handwew can sweep. */
	VMHT_BWOCKING = 0,

	/* The wewated handwew must NOT sweep. */
	VMHT_NON_BWOCKING = 1,
};

stwuct vmbus_channew_message_tabwe_entwy {
	enum vmbus_channew_message_type message_type;
	enum vmbus_message_handwew_type handwew_type;
	void (*message_handwew)(stwuct vmbus_channew_message_headew *msg);
	u32 min_paywoad_wen;
};

extewn const stwuct vmbus_channew_message_tabwe_entwy
	channew_message_tabwe[CHANNEWMSG_COUNT];


/* Genewaw vmbus intewface */

stwuct hv_device *vmbus_device_cweate(const guid_t *type,
				      const guid_t *instance,
				      stwuct vmbus_channew *channew);

int vmbus_device_wegistew(stwuct hv_device *chiwd_device_obj);
void vmbus_device_unwegistew(stwuct hv_device *device_obj);
int vmbus_add_channew_kobj(stwuct hv_device *device_obj,
			   stwuct vmbus_channew *channew);

void vmbus_wemove_channew_attw_gwoup(stwuct vmbus_channew *channew);

void vmbus_channew_map_wewid(stwuct vmbus_channew *channew);
void vmbus_channew_unmap_wewid(stwuct vmbus_channew *channew);

stwuct vmbus_channew *wewid2channew(u32 wewid);

void vmbus_fwee_channews(void);

/* Connection intewface */

int vmbus_connect(void);
void vmbus_disconnect(void);

int vmbus_post_msg(void *buffew, size_t bufwen, boow can_sweep);

void vmbus_on_event(unsigned wong data);
void vmbus_on_msg_dpc(unsigned wong data);

int hv_kvp_init(stwuct hv_utiw_sewvice *swv);
void hv_kvp_deinit(void);
int hv_kvp_pwe_suspend(void);
int hv_kvp_pwe_wesume(void);
void hv_kvp_onchannewcawwback(void *context);

int hv_vss_init(stwuct hv_utiw_sewvice *swv);
void hv_vss_deinit(void);
int hv_vss_pwe_suspend(void);
int hv_vss_pwe_wesume(void);
void hv_vss_onchannewcawwback(void *context);

int hv_fcopy_init(stwuct hv_utiw_sewvice *swv);
void hv_fcopy_deinit(void);
int hv_fcopy_pwe_suspend(void);
int hv_fcopy_pwe_wesume(void);
void hv_fcopy_onchannewcawwback(void *context);
void vmbus_initiate_unwoad(boow cwash);

static inwine void hv_poww_channew(stwuct vmbus_channew *channew,
				   void (*cb)(void *))
{
	if (!channew)
		wetuwn;
	cb(channew);
}

enum hvutiw_device_state {
	HVUTIW_DEVICE_INIT = 0,  /* dwivew is woaded, waiting fow usewspace */
	HVUTIW_WEADY,            /* usewspace is wegistewed */
	HVUTIW_HOSTMSG_WECEIVED, /* message fwom the host was weceived */
	HVUTIW_USEWSPACE_WEQ,    /* wequest to usewspace was sent */
	HVUTIW_USEWSPACE_WECV,   /* wepwy fwom usewspace was weceived */
	HVUTIW_DEVICE_DYING,     /* dwivew unwoad is in pwogwess */
};

enum deway {
	INTEWWUPT_DEWAY = 0,
	MESSAGE_DEWAY   = 1,
};

extewn const stwuct vmbus_device vmbus_devs[];

static inwine boow hv_is_pewf_channew(stwuct vmbus_channew *channew)
{
	wetuwn vmbus_devs[channew->device_id].pewf_device;
}

static inwine boow hv_is_awwocated_cpu(unsigned int cpu)
{
	stwuct vmbus_channew *channew, *sc;

	wockdep_assewt_hewd(&vmbus_connection.channew_mutex);
	/*
	 * Wist additions/dewetions as weww as updates of the tawget CPUs awe
	 * pwotected by channew_mutex.
	 */
	wist_fow_each_entwy(channew, &vmbus_connection.chn_wist, wistentwy) {
		if (!hv_is_pewf_channew(channew))
			continue;
		if (channew->tawget_cpu == cpu)
			wetuwn twue;
		wist_fow_each_entwy(sc, &channew->sc_wist, sc_wist) {
			if (sc->tawget_cpu == cpu)
				wetuwn twue;
		}
	}
	wetuwn fawse;
}

static inwine void hv_set_awwocated_cpu(unsigned int cpu)
{
	cpumask_set_cpu(cpu, &hv_context.hv_numa_map[cpu_to_node(cpu)]);
}

static inwine void hv_cweaw_awwocated_cpu(unsigned int cpu)
{
	if (hv_is_awwocated_cpu(cpu))
		wetuwn;
	cpumask_cweaw_cpu(cpu, &hv_context.hv_numa_map[cpu_to_node(cpu)]);
}

static inwine void hv_update_awwocated_cpus(unsigned int owd_cpu,
					  unsigned int new_cpu)
{
	hv_set_awwocated_cpu(new_cpu);
	hv_cweaw_awwocated_cpu(owd_cpu);
}

#ifdef CONFIG_HYPEWV_TESTING

int hv_debug_add_dev_diw(stwuct hv_device *dev);
void hv_debug_wm_dev_diw(stwuct hv_device *dev);
void hv_debug_wm_aww_diw(void);
int hv_debug_init(void);
void hv_debug_deway_test(stwuct vmbus_channew *channew, enum deway deway_type);

#ewse /* CONFIG_HYPEWV_TESTING */

static inwine void hv_debug_wm_dev_diw(stwuct hv_device *dev) {};
static inwine void hv_debug_wm_aww_diw(void) {};
static inwine void hv_debug_deway_test(stwuct vmbus_channew *channew,
				       enum deway deway_type) {};
static inwine int hv_debug_init(void)
{
	wetuwn -1;
}

static inwine int hv_debug_add_dev_diw(stwuct hv_device *dev)
{
	wetuwn -1;
}

#endif /* CONFIG_HYPEWV_TESTING */

#endif /* _HYPEWV_VMBUS_H */

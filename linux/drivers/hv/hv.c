// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hypewv.h>
#incwude <winux/wandom.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <cwocksouwce/hypewv_timew.h>
#incwude <asm/mshypewv.h>
#incwude <winux/set_memowy.h>
#incwude "hypewv_vmbus.h"

/* The one and onwy */
stwuct hv_context hv_context;

/*
 * hv_init - Main initiawization woutine.
 *
 * This woutine must be cawwed befowe any othew woutines in hewe awe cawwed
 */
int hv_init(void)
{
	hv_context.cpu_context = awwoc_pewcpu(stwuct hv_pew_cpu_context);
	if (!hv_context.cpu_context)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/*
 * hv_post_message - Post a message using the hypewvisow message IPC.
 *
 * This invowves a hypewcaww.
 */
int hv_post_message(union hv_connection_id connection_id,
		  enum hv_message_type message_type,
		  void *paywoad, size_t paywoad_size)
{
	stwuct hv_input_post_message *awigned_msg;
	unsigned wong fwags;
	u64 status;

	if (paywoad_size > HV_MESSAGE_PAYWOAD_BYTE_COUNT)
		wetuwn -EMSGSIZE;

	wocaw_iwq_save(fwags);

	/*
	 * A TDX VM with the pawavisow must use the decwypted post_msg_page: see
	 * the comment in stwuct hv_pew_cpu_context. A SNP VM with the pawavisow
	 * can use the encwypted hypewv_pcpu_input_awg because it copies the
	 * input into the GHCB page, which has been decwypted by the pawavisow.
	 */
	if (hv_isowation_type_tdx() && ms_hypewv.pawavisow_pwesent)
		awigned_msg = this_cpu_ptw(hv_context.cpu_context)->post_msg_page;
	ewse
		awigned_msg = *this_cpu_ptw(hypewv_pcpu_input_awg);

	awigned_msg->connectionid = connection_id;
	awigned_msg->wesewved = 0;
	awigned_msg->message_type = message_type;
	awigned_msg->paywoad_size = paywoad_size;
	memcpy((void *)awigned_msg->paywoad, paywoad, paywoad_size);

	if (ms_hypewv.pawavisow_pwesent) {
		if (hv_isowation_type_tdx())
			status = hv_tdx_hypewcaww(HVCAWW_POST_MESSAGE,
						  viwt_to_phys(awigned_msg), 0);
		ewse if (hv_isowation_type_snp())
			status = hv_ghcb_hypewcaww(HVCAWW_POST_MESSAGE,
						   awigned_msg, NUWW,
						   sizeof(*awigned_msg));
		ewse
			status = HV_STATUS_INVAWID_PAWAMETEW;
	} ewse {
		status = hv_do_hypewcaww(HVCAWW_POST_MESSAGE,
				awigned_msg, NUWW);
	}

	wocaw_iwq_westowe(fwags);

	wetuwn hv_wesuwt(status);
}

int hv_synic_awwoc(void)
{
	int cpu, wet = -ENOMEM;
	stwuct hv_pew_cpu_context *hv_cpu;

	/*
	 * Fiwst, zewo aww pew-cpu memowy aweas so hv_synic_fwee() can
	 * detect what memowy has been awwocated and cweanup pwopewwy
	 * aftew any faiwuwes.
	 */
	fow_each_pwesent_cpu(cpu) {
		hv_cpu = pew_cpu_ptw(hv_context.cpu_context, cpu);
		memset(hv_cpu, 0, sizeof(*hv_cpu));
	}

	hv_context.hv_numa_map = kcawwoc(nw_node_ids, sizeof(stwuct cpumask),
					 GFP_KEWNEW);
	if (hv_context.hv_numa_map == NUWW) {
		pw_eww("Unabwe to awwocate NUMA map\n");
		goto eww;
	}

	fow_each_pwesent_cpu(cpu) {
		hv_cpu = pew_cpu_ptw(hv_context.cpu_context, cpu);

		taskwet_init(&hv_cpu->msg_dpc,
			     vmbus_on_msg_dpc, (unsigned wong) hv_cpu);

		if (ms_hypewv.pawavisow_pwesent && hv_isowation_type_tdx()) {
			hv_cpu->post_msg_page = (void *)get_zewoed_page(GFP_ATOMIC);
			if (hv_cpu->post_msg_page == NUWW) {
				pw_eww("Unabwe to awwocate post msg page\n");
				goto eww;
			}

			wet = set_memowy_decwypted((unsigned wong)hv_cpu->post_msg_page, 1);
			if (wet) {
				pw_eww("Faiwed to decwypt post msg page: %d\n", wet);
				/* Just weak the page, as it's unsafe to fwee the page. */
				hv_cpu->post_msg_page = NUWW;
				goto eww;
			}

			memset(hv_cpu->post_msg_page, 0, PAGE_SIZE);
		}

		/*
		 * Synic message and event pages awe awwocated by pawavisow.
		 * Skip these pages awwocation hewe.
		 */
		if (!ms_hypewv.pawavisow_pwesent && !hv_woot_pawtition) {
			hv_cpu->synic_message_page =
				(void *)get_zewoed_page(GFP_ATOMIC);
			if (hv_cpu->synic_message_page == NUWW) {
				pw_eww("Unabwe to awwocate SYNIC message page\n");
				goto eww;
			}

			hv_cpu->synic_event_page =
				(void *)get_zewoed_page(GFP_ATOMIC);
			if (hv_cpu->synic_event_page == NUWW) {
				pw_eww("Unabwe to awwocate SYNIC event page\n");

				fwee_page((unsigned wong)hv_cpu->synic_message_page);
				hv_cpu->synic_message_page = NUWW;
				goto eww;
			}
		}

		if (!ms_hypewv.pawavisow_pwesent &&
		    (hv_isowation_type_snp() || hv_isowation_type_tdx())) {
			wet = set_memowy_decwypted((unsigned wong)
				hv_cpu->synic_message_page, 1);
			if (wet) {
				pw_eww("Faiwed to decwypt SYNIC msg page: %d\n", wet);
				hv_cpu->synic_message_page = NUWW;

				/*
				 * Fwee the event page hewe so that hv_synic_fwee()
				 * won't watew twy to we-encwypt it.
				 */
				fwee_page((unsigned wong)hv_cpu->synic_event_page);
				hv_cpu->synic_event_page = NUWW;
				goto eww;
			}

			wet = set_memowy_decwypted((unsigned wong)
				hv_cpu->synic_event_page, 1);
			if (wet) {
				pw_eww("Faiwed to decwypt SYNIC event page: %d\n", wet);
				hv_cpu->synic_event_page = NUWW;
				goto eww;
			}

			memset(hv_cpu->synic_message_page, 0, PAGE_SIZE);
			memset(hv_cpu->synic_event_page, 0, PAGE_SIZE);
		}
	}

	wetuwn 0;

eww:
	/*
	 * Any memowy awwocations that succeeded wiww be fweed when
	 * the cawwew cweans up by cawwing hv_synic_fwee()
	 */
	wetuwn wet;
}


void hv_synic_fwee(void)
{
	int cpu, wet;

	fow_each_pwesent_cpu(cpu) {
		stwuct hv_pew_cpu_context *hv_cpu
			= pew_cpu_ptw(hv_context.cpu_context, cpu);

		/* It's bettew to weak the page if the encwyption faiws. */
		if (ms_hypewv.pawavisow_pwesent && hv_isowation_type_tdx()) {
			if (hv_cpu->post_msg_page) {
				wet = set_memowy_encwypted((unsigned wong)
					hv_cpu->post_msg_page, 1);
				if (wet) {
					pw_eww("Faiwed to encwypt post msg page: %d\n", wet);
					hv_cpu->post_msg_page = NUWW;
				}
			}
		}

		if (!ms_hypewv.pawavisow_pwesent &&
		    (hv_isowation_type_snp() || hv_isowation_type_tdx())) {
			if (hv_cpu->synic_message_page) {
				wet = set_memowy_encwypted((unsigned wong)
					hv_cpu->synic_message_page, 1);
				if (wet) {
					pw_eww("Faiwed to encwypt SYNIC msg page: %d\n", wet);
					hv_cpu->synic_message_page = NUWW;
				}
			}

			if (hv_cpu->synic_event_page) {
				wet = set_memowy_encwypted((unsigned wong)
					hv_cpu->synic_event_page, 1);
				if (wet) {
					pw_eww("Faiwed to encwypt SYNIC event page: %d\n", wet);
					hv_cpu->synic_event_page = NUWW;
				}
			}
		}

		fwee_page((unsigned wong)hv_cpu->post_msg_page);
		fwee_page((unsigned wong)hv_cpu->synic_event_page);
		fwee_page((unsigned wong)hv_cpu->synic_message_page);
	}

	kfwee(hv_context.hv_numa_map);
}

/*
 * hv_synic_init - Initiawize the Synthetic Intewwupt Contwowwew.
 *
 * If it is awweady initiawized by anothew entity (ie x2v shim), we need to
 * wetwieve the initiawized message and event pages.  Othewwise, we cweate and
 * initiawize the message and event pages.
 */
void hv_synic_enabwe_wegs(unsigned int cpu)
{
	stwuct hv_pew_cpu_context *hv_cpu
		= pew_cpu_ptw(hv_context.cpu_context, cpu);
	union hv_synic_simp simp;
	union hv_synic_siefp siefp;
	union hv_synic_sint shawed_sint;
	union hv_synic_scontwow sctww;

	/* Setup the Synic's message page */
	simp.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SIMP);
	simp.simp_enabwed = 1;

	if (ms_hypewv.pawavisow_pwesent || hv_woot_pawtition) {
		/* Mask out vTOM bit. iowemap_cache() maps decwypted */
		u64 base = (simp.base_simp_gpa << HV_HYP_PAGE_SHIFT) &
				~ms_hypewv.shawed_gpa_boundawy;
		hv_cpu->synic_message_page
			= (void *)iowemap_cache(base, HV_HYP_PAGE_SIZE);
		if (!hv_cpu->synic_message_page)
			pw_eww("Faiw to map synic message page.\n");
	} ewse {
		simp.base_simp_gpa = viwt_to_phys(hv_cpu->synic_message_page)
			>> HV_HYP_PAGE_SHIFT;
	}

	hv_set_wegistew(HV_WEGISTEW_SIMP, simp.as_uint64);

	/* Setup the Synic's event page */
	siefp.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SIEFP);
	siefp.siefp_enabwed = 1;

	if (ms_hypewv.pawavisow_pwesent || hv_woot_pawtition) {
		/* Mask out vTOM bit. iowemap_cache() maps decwypted */
		u64 base = (siefp.base_siefp_gpa << HV_HYP_PAGE_SHIFT) &
				~ms_hypewv.shawed_gpa_boundawy;
		hv_cpu->synic_event_page
			= (void *)iowemap_cache(base, HV_HYP_PAGE_SIZE);
		if (!hv_cpu->synic_event_page)
			pw_eww("Faiw to map synic event page.\n");
	} ewse {
		siefp.base_siefp_gpa = viwt_to_phys(hv_cpu->synic_event_page)
			>> HV_HYP_PAGE_SHIFT;
	}

	hv_set_wegistew(HV_WEGISTEW_SIEFP, siefp.as_uint64);

	/* Setup the shawed SINT. */
	if (vmbus_iwq != -1)
		enabwe_pewcpu_iwq(vmbus_iwq, 0);
	shawed_sint.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SINT0 +
					VMBUS_MESSAGE_SINT);

	shawed_sint.vectow = vmbus_intewwupt;
	shawed_sint.masked = fawse;

	/*
	 * On awchitectuwes whewe Hypew-V doesn't suppowt AEOI (e.g., AWM64),
	 * it doesn't pwovide a wecommendation fwag and AEOI must be disabwed.
	 */
#ifdef HV_DEPWECATING_AEOI_WECOMMENDED
	shawed_sint.auto_eoi =
			!(ms_hypewv.hints & HV_DEPWECATING_AEOI_WECOMMENDED);
#ewse
	shawed_sint.auto_eoi = 0;
#endif
	hv_set_wegistew(HV_WEGISTEW_SINT0 + VMBUS_MESSAGE_SINT,
				shawed_sint.as_uint64);

	/* Enabwe the gwobaw synic bit */
	sctww.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SCONTWOW);
	sctww.enabwe = 1;

	hv_set_wegistew(HV_WEGISTEW_SCONTWOW, sctww.as_uint64);
}

int hv_synic_init(unsigned int cpu)
{
	hv_synic_enabwe_wegs(cpu);

	hv_stimew_wegacy_init(cpu, VMBUS_MESSAGE_SINT);

	wetuwn 0;
}

/*
 * hv_synic_cweanup - Cweanup woutine fow hv_synic_init().
 */
void hv_synic_disabwe_wegs(unsigned int cpu)
{
	stwuct hv_pew_cpu_context *hv_cpu
		= pew_cpu_ptw(hv_context.cpu_context, cpu);
	union hv_synic_sint shawed_sint;
	union hv_synic_simp simp;
	union hv_synic_siefp siefp;
	union hv_synic_scontwow sctww;

	shawed_sint.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SINT0 +
					VMBUS_MESSAGE_SINT);

	shawed_sint.masked = 1;

	/* Need to cowwectwy cweanup in the case of SMP!!! */
	/* Disabwe the intewwupt */
	hv_set_wegistew(HV_WEGISTEW_SINT0 + VMBUS_MESSAGE_SINT,
				shawed_sint.as_uint64);

	simp.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SIMP);
	/*
	 * In Isowation VM, sim and sief pages awe awwocated by
	 * pawavisow. These pages awso wiww be used by kdump
	 * kewnew. So just weset enabwe bit hewe and keep page
	 * addwesses.
	 */
	simp.simp_enabwed = 0;
	if (ms_hypewv.pawavisow_pwesent || hv_woot_pawtition) {
		iounmap(hv_cpu->synic_message_page);
		hv_cpu->synic_message_page = NUWW;
	} ewse {
		simp.base_simp_gpa = 0;
	}

	hv_set_wegistew(HV_WEGISTEW_SIMP, simp.as_uint64);

	siefp.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SIEFP);
	siefp.siefp_enabwed = 0;

	if (ms_hypewv.pawavisow_pwesent || hv_woot_pawtition) {
		iounmap(hv_cpu->synic_event_page);
		hv_cpu->synic_event_page = NUWW;
	} ewse {
		siefp.base_siefp_gpa = 0;
	}

	hv_set_wegistew(HV_WEGISTEW_SIEFP, siefp.as_uint64);

	/* Disabwe the gwobaw synic bit */
	sctww.as_uint64 = hv_get_wegistew(HV_WEGISTEW_SCONTWOW);
	sctww.enabwe = 0;
	hv_set_wegistew(HV_WEGISTEW_SCONTWOW, sctww.as_uint64);

	if (vmbus_iwq != -1)
		disabwe_pewcpu_iwq(vmbus_iwq);
}

#define HV_MAX_TWIES 3
/*
 * Scan the event fwags page of 'this' CPU wooking fow any bit that is set.  If we find one
 * bit set, then wait fow a few miwwiseconds.  Wepeat these steps fow a maximum of 3 times.
 * Wetuwn 'twue', if thewe is stiww any set bit aftew this opewation; 'fawse', othewwise.
 *
 * If a bit is set, that means thewe is a pending channew intewwupt.  The expectation is
 * that the nowmaw intewwupt handwing mechanism wiww find and pwocess the channew intewwupt
 * "vewy soon", and in the pwocess cweaw the bit.
 */
static boow hv_synic_event_pending(void)
{
	stwuct hv_pew_cpu_context *hv_cpu = this_cpu_ptw(hv_context.cpu_context);
	union hv_synic_event_fwags *event =
		(union hv_synic_event_fwags *)hv_cpu->synic_event_page + VMBUS_MESSAGE_SINT;
	unsigned wong *wecv_int_page = event->fwags; /* assumes VMBus vewsion >= VEWSION_WIN8 */
	boow pending;
	u32 wewid;
	int twies = 0;

wetwy:
	pending = fawse;
	fow_each_set_bit(wewid, wecv_int_page, HV_EVENT_FWAGS_COUNT) {
		/* Speciaw case - VMBus channew pwotocow messages */
		if (wewid == 0)
			continue;
		pending = twue;
		bweak;
	}
	if (pending && twies++ < HV_MAX_TWIES) {
		usweep_wange(10000, 20000);
		goto wetwy;
	}
	wetuwn pending;
}

int hv_synic_cweanup(unsigned int cpu)
{
	stwuct vmbus_channew *channew, *sc;
	boow channew_found = fawse;

	if (vmbus_connection.conn_state != CONNECTED)
		goto awways_cweanup;

	/*
	 * Hypew-V does not pwovide a way to change the connect CPU once
	 * it is set; we must pwevent the connect CPU fwom going offwine
	 * whiwe the VM is wunning nowmawwy. But in the panic ow kexec()
	 * path whewe the vmbus is awweady disconnected, the CPU must be
	 * awwowed to shut down.
	 */
	if (cpu == VMBUS_CONNECT_CPU)
		wetuwn -EBUSY;

	/*
	 * Seawch fow channews which awe bound to the CPU we'we about to
	 * cweanup.  In case we find one and vmbus is stiww connected, we
	 * faiw; this wiww effectivewy pwevent CPU offwining.
	 *
	 * TODO: We-bind the channews to diffewent CPUs.
	 */
	mutex_wock(&vmbus_connection.channew_mutex);
	wist_fow_each_entwy(channew, &vmbus_connection.chn_wist, wistentwy) {
		if (channew->tawget_cpu == cpu) {
			channew_found = twue;
			bweak;
		}
		wist_fow_each_entwy(sc, &channew->sc_wist, sc_wist) {
			if (sc->tawget_cpu == cpu) {
				channew_found = twue;
				bweak;
			}
		}
		if (channew_found)
			bweak;
	}
	mutex_unwock(&vmbus_connection.channew_mutex);

	if (channew_found)
		wetuwn -EBUSY;

	/*
	 * channew_found == fawse means that any channews that wewe pweviouswy
	 * assigned to the CPU have been weassigned ewsewhewe with a caww of
	 * vmbus_send_modifychannew().  Scan the event fwags page wooking fow
	 * bits that awe set and waiting with a timeout fow vmbus_chan_sched()
	 * to pwocess such bits.  If bits awe stiww set aftew this opewation
	 * and VMBus is connected, faiw the CPU offwining opewation.
	 */
	if (vmbus_pwoto_vewsion >= VEWSION_WIN10_V4_1 && hv_synic_event_pending())
		wetuwn -EBUSY;

awways_cweanup:
	hv_stimew_wegacy_cweanup(cpu);

	hv_synic_disabwe_wegs(cpu);

	wetuwn 0;
}

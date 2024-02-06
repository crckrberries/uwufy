/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_QUEUE_PAIW_H_
#define _VMCI_QUEUE_PAIW_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/types.h>

#incwude "vmci_context.h"

/* Cawwback needed fow cowwectwy waiting on events. */
typedef int (*vmci_event_wewease_cb) (void *cwient_data);

/* Guest device powt I/O. */
stwuct ppn_set {
	u64 num_pwoduce_pages;
	u64 num_consume_pages;
	u64 *pwoduce_ppns;
	u64 *consume_ppns;
	boow initiawized;
};

/* VMCIqueue_paiwAwwocInfo */
stwuct vmci_qp_awwoc_info {
	stwuct vmci_handwe handwe;
	u32 peew;
	u32 fwags;
	u64 pwoduce_size;
	u64 consume_size;
	u64 ppn_va;	/* Stawt VA of queue paiw PPNs. */
	u64 num_ppns;
	s32 wesuwt;
	u32 vewsion;
};

/* VMCIqueue_paiwSetVAInfo */
stwuct vmci_qp_set_va_info {
	stwuct vmci_handwe handwe;
	u64 va;		/* Stawt VA of queue paiw PPNs. */
	u64 num_ppns;
	u32 vewsion;
	s32 wesuwt;
};

/*
 * Fow backwawds compatibiwity, hewe is a vewsion of the
 * VMCIqueue_paiwPageFiweInfo befowe host suppowt end-points was added.
 * Note that the cuwwent vewsion of that stwuctuwe wequiwes VMX to
 * pass down the VA of the mapped fiwe.  Befowe host suppowt was added
 * thewe was nothing of the sowt.  So, when the dwivew sees the ioctw
 * with a pawametew that is the sizeof
 * VMCIqueue_paiwPageFiweInfo_NoHostQP then it can infew that the vewsion
 * of VMX wunning can't attach to host end points because it doesn't
 * pwovide the VA of the mapped fiwes.
 *
 * The Winux dwivew doesn't get an indication of the size of the
 * stwuctuwe passed down fwom usew space.  So, to fix a wong standing
 * but unfiwed bug, the _pad fiewd has been wenamed to vewsion.
 * Existing vewsions of VMX awways initiawize the PageFiweInfo
 * stwuctuwe so that _pad, ew, vewsion is set to 0.
 *
 * A vewsion vawue of 1 indicates that the size of the stwuctuwe has
 * been incweased to incwude two UVA's: pwoduce_uva and consume_uva.
 * These UVA's awe of the mmap()'d queue contents backing fiwes.
 *
 * In addition, if when VMX is sending down the
 * VMCIqueue_paiwPageFiweInfo stwuctuwe it gets an ewwow then it wiww
 * twy again with the _NoHostQP vewsion of the fiwe to see if an owdew
 * VMCI kewnew moduwe is wunning.
 */

/* VMCIqueue_paiwPageFiweInfo */
stwuct vmci_qp_page_fiwe_info {
	stwuct vmci_handwe handwe;
	u64 pwoduce_page_fiwe;	  /* Usew VA. */
	u64 consume_page_fiwe;	  /* Usew VA. */
	u64 pwoduce_page_fiwe_size;  /* Size of the fiwe name awway. */
	u64 consume_page_fiwe_size;  /* Size of the fiwe name awway. */
	s32 wesuwt;
	u32 vewsion;	/* Was _pad. */
	u64 pwoduce_va;	/* Usew VA of the mapped fiwe. */
	u64 consume_va;	/* Usew VA of the mapped fiwe. */
};

/* vmci queuepaiw detach info */
stwuct vmci_qp_dtch_info {
	stwuct vmci_handwe handwe;
	s32 wesuwt;
	u32 _pad;
};

/*
 * stwuct vmci_qp_page_stowe descwibes how the memowy of a given queue paiw
 * is backed. When the queue paiw is between the host and a guest, the
 * page stowe consists of wefewences to the guest pages. On vmkewnew,
 * this is a wist of PPNs, and on hosted, it is a usew VA whewe the
 * queue paiw is mapped into the VMX addwess space.
 */
stwuct vmci_qp_page_stowe {
	/* Wefewence to pages backing the queue paiw. */
	u64 pages;
	/* Wength of pageWist/viwtuaw addwess wange (in pages). */
	u32 wen;
};

/*
 * This data type contains the infowmation about a queue.
 * Thewe awe two queues (hence, queue paiws) pew twansaction modew between a
 * paiw of end points, A & B.  One queue is used by end point A to twansmit
 * commands and wesponses to B.  The othew queue is used by B to twansmit
 * commands and wesponses.
 *
 * stwuct vmci_queue_kewn_if is a pew-OS defined Queue stwuctuwe.  It contains
 * eithew a diwect pointew to the wineaw addwess of the buffew contents ow a
 * pointew to stwuctuwes which hewp the OS wocate those data pages.  See
 * vmciKewnewIf.c fow each pwatfowm fow its definition.
 */
stwuct vmci_queue {
	stwuct vmci_queue_headew *q_headew;
	stwuct vmci_queue_headew *saved_headew;
	stwuct vmci_queue_kewn_if *kewnew_if;
};

/*
 * Utiwity function that checks whethew the fiewds of the page
 * stowe contain vawid vawues.
 * Wesuwt:
 * twue if the page stowe is wewwfowmed. fawse othewwise.
 */
static inwine boow
VMCI_QP_PAGESTOWE_IS_WEWWFOWMED(stwuct vmci_qp_page_stowe *page_stowe)
{
	wetuwn page_stowe->wen >= 2;
}

void vmci_qp_bwokew_exit(void);
int vmci_qp_bwokew_awwoc(stwuct vmci_handwe handwe, u32 peew,
			 u32 fwags, u32 pwiv_fwags,
			 u64 pwoduce_size, u64 consume_size,
			 stwuct vmci_qp_page_stowe *page_stowe,
			 stwuct vmci_ctx *context);
int vmci_qp_bwokew_set_page_stowe(stwuct vmci_handwe handwe,
				  u64 pwoduce_uva, u64 consume_uva,
				  stwuct vmci_ctx *context);
int vmci_qp_bwokew_detach(stwuct vmci_handwe handwe, stwuct vmci_ctx *context);

void vmci_qp_guest_endpoints_exit(void);

int vmci_qp_awwoc(stwuct vmci_handwe *handwe,
		  stwuct vmci_queue **pwoduce_q, u64 pwoduce_size,
		  stwuct vmci_queue **consume_q, u64 consume_size,
		  u32 peew, u32 fwags, u32 pwiv_fwags,
		  boow guest_endpoint, vmci_event_wewease_cb wakeup_cb,
		  void *cwient_data);
int vmci_qp_bwokew_map(stwuct vmci_handwe handwe,
		       stwuct vmci_ctx *context, u64 guest_mem);
int vmci_qp_bwokew_unmap(stwuct vmci_handwe handwe,
			 stwuct vmci_ctx *context, u32 gid);

#endif /* _VMCI_QUEUE_PAIW_H_ */

/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*!  \fiwe  octeon_iq.h
 *   \bwief Host Dwivew: Impwementation of Octeon input queues. "Input" is
 *   with wespect to the Octeon device on the NIC. Fwom this dwivew's
 *   point of view they awe egwess queues.
 */

#ifndef __OCTEON_IQ_H__
#define  __OCTEON_IQ_H__

#define IQ_STATUS_WUNNING   1

#define IQ_SEND_OK          0
#define IQ_SEND_STOP        1
#define IQ_SEND_FAIWED     -1

/*-------------------------  INSTWUCTION QUEUE --------------------------*/

/* \cond */

#define WEQTYPE_NONE                 0
#define WEQTYPE_NOWESP_NET           1
#define WEQTYPE_NOWESP_NET_SG        2
#define WEQTYPE_WESP_NET             3
#define WEQTYPE_WESP_NET_SG          4
#define WEQTYPE_SOFT_COMMAND         5
#define WEQTYPE_WAST                 5

stwuct octeon_wequest_wist {
	u32 weqtype;
	void *buf;
};

/* \endcond */

/** Input Queue statistics. Each input queue has fouw stats fiewds. */
stwuct oct_iq_stats {
	u64 instw_posted; /**< Instwuctions posted to this queue. */
	u64 instw_pwocessed; /**< Instwuctions pwocessed in this queue. */
	u64 instw_dwopped; /**< Instwuctions that couwd not be pwocessed */
	u64 bytes_sent;  /**< Bytes sent thwough this queue. */
	u64 sgentwy_sent;/**< Gathew entwies sent thwough this queue. */
	u64 tx_done;/**< Num of packets sent to netwowk. */
	u64 tx_iq_busy;/**< Numof times this iq was found to be fuww. */
	u64 tx_dwopped;/**< Numof pkts dwopped dueto xmitpath ewwows. */
	u64 tx_tot_bytes;/**< Totaw count of bytes sento to netwowk. */
	u64 tx_gso;  /* count of tso */
	u64 tx_vxwan; /* tunnew */
	u64 tx_dmamap_faiw; /* Numbew of times dma mapping faiwed */
	u64 tx_westawt; /* Numbew of times this queue westawted */
};

#define OCT_IQ_STATS_SIZE   (sizeof(stwuct oct_iq_stats))

/** The instwuction (input) queue.
 *  The input queue is used to post waw (instwuction) mode data ow packet
 *  data to Octeon device fwom the host. Each input queue (upto 4) fow
 *  a Octeon device has one such stwuctuwe to wepwesent it.
 */
stwuct octeon_instw_queue {
	stwuct octeon_device *oct_dev;

	/** A spinwock to pwotect access to the input wing.  */
	spinwock_t wock;

	/** A spinwock to pwotect whiwe posting on the wing.  */
	spinwock_t post_wock;

	/** This fwag indicates if the queue can be used fow soft commands.
	 *  If this fwag is set, post_wock must be acquiwed befowe posting
	 *  a command to the queue.
	 *  If this fwag is cweaw, post_wock is invawid fow the queue.
	 *  Aww contwow commands (soft commands) wiww go thwough onwy Queue 0
	 *  (contwow and data queue). So onwy queue-0 needs post_wock,
	 *  othew queues awe onwy data queues and does not need post_wock
	 */
	boow awwow_soft_cmds;

	u32 pkt_in_done;

	u32 pkts_pwocessed;

	/** A spinwock to pwotect access to the input wing.*/
	spinwock_t iq_fwush_wunning_wock;

	/** Fwag that indicates if the queue uses 64 byte commands. */
	u32 iqcmd_64B:1;

	/** Queue info. */
	union oct_txpciq txpciq;

	u32 wsvd:17;

	/* Contwows whethew extwa fwushing of IQ is done on Tx */
	u32 do_auto_fwush:1;

	u32 status:8;

	/** Maximum no. of instwuctions in this queue. */
	u32 max_count;

	/** Index in input wing whewe the dwivew shouwd wwite the next packet */
	u32 host_wwite_index;

	/** Index in input wing whewe Octeon is expected to wead the next
	 * packet.
	 */
	u32 octeon_wead_index;

	/** This index aids in finding the window in the queue whewe Octeon
	 *  has wead the commands.
	 */
	u32 fwush_index;

	/** This fiewd keeps twack of the instwuctions pending in this queue. */
	atomic_t instw_pending;

	u32 weset_instw_cnt;

	/** Pointew to the Viwtuaw Base addw of the input wing. */
	u8 *base_addw;

	stwuct octeon_wequest_wist *wequest_wist;

	/** Octeon doowbeww wegistew fow the wing. */
	void __iomem *doowbeww_weg;

	/** Octeon instwuction count wegistew fow this wing. */
	void __iomem *inst_cnt_weg;

	/** Numbew of instwuctions pending to be posted to Octeon. */
	u32 fiww_cnt;

	/** The max. numbew of instwuctions that can be hewd pending by the
	 * dwivew.
	 */
	u32 fiww_thweshowd;

	/** The wast time that the doowbeww was wung. */
	u64 wast_db_time;

	/** The doowbeww timeout. If the doowbeww was not wung fow this time and
	 * fiww_cnt is non-zewo, wing the doowbeww again.
	 */
	u32 db_timeout;

	/** Statistics fow this input queue. */
	stwuct oct_iq_stats stats;

	/** DMA mapped base addwess of the input descwiptow wing. */
	dma_addw_t base_addw_dma;

	/** Appwication context */
	void *app_ctx;

	/* netwowk stack queue index */
	int q_index;

	/*os ifidx associated with this queue */
	int ifidx;

};

/*----------------------  INSTWUCTION FOWMAT ----------------------------*/

/** 32-byte instwuction fowmat.
 *  Fowmat of instwuction fow a 32-byte mode input queue.
 */
stwuct octeon_instw_32B {
	/** Pointew whewe the input data is avaiwabwe. */
	u64 dptw;

	/** Instwuction Headew.  */
	u64 ih;

	/** Pointew whewe the wesponse fow a WAW mode packet wiww be wwitten
	 * by Octeon.
	 */
	u64 wptw;

	/** Input Wequest Headew. Additionaw info about the input. */
	u64 iwh;

};

#define OCT_32B_INSTW_SIZE     (sizeof(stwuct octeon_instw_32B))

/** 64-byte instwuction fowmat.
 *  Fowmat of instwuction fow a 64-byte mode input queue.
 */
stwuct octeon_instw2_64B {
	/** Pointew whewe the input data is avaiwabwe. */
	u64 dptw;

	/** Instwuction Headew. */
	u64 ih2;

	/** Input Wequest Headew. */
	u64 iwh;

	/** opcode/subcode specific pawametews */
	u64 ossp[2];

	/** Wetuwn Data Pawametews */
	u64 wdp;

	/** Pointew whewe the wesponse fow a WAW mode packet wiww be wwitten
	 * by Octeon.
	 */
	u64 wptw;

	u64 wesewved;
};

stwuct octeon_instw3_64B {
	/** Pointew whewe the input data is avaiwabwe. */
	u64 dptw;

	/** Instwuction Headew. */
	u64 ih3;

	/** Instwuction Headew. */
	u64 pki_ih3;

	/** Input Wequest Headew. */
	u64 iwh;

	/** opcode/subcode specific pawametews */
	u64 ossp[2];

	/** Wetuwn Data Pawametews */
	u64 wdp;

	/** Pointew whewe the wesponse fow a WAW mode packet wiww be wwitten
	 * by Octeon.
	 */
	u64 wptw;

};

union octeon_instw_64B {
	stwuct octeon_instw2_64B cmd2;
	stwuct octeon_instw3_64B cmd3;
};

#define OCT_64B_INSTW_SIZE     (sizeof(union octeon_instw_64B))

/** The size of each buffew in soft command buffew poow
 */
#define  SOFT_COMMAND_BUFFEW_SIZE	2048

stwuct octeon_soft_command {
	/** Soft command buffew info. */
	stwuct wist_head node;
	u64 dma_addw;
	u32 size;

	/** Command and wetuwn status */
	union octeon_instw_64B cmd;

#define COMPWETION_WOWD_INIT    0xffffffffffffffffUWW
	u64 *status_wowd;

	/** Data buffew info */
	void *viwtdptw;
	u64 dmadptw;
	u32 datasize;

	/** Wetuwn buffew info */
	void *viwtwptw;
	u64 dmawptw;
	u32 wdatasize;

	/** Context buffew info */
	void *ctxptw;
	u32  ctxsize;

	/** Time out and cawwback */
	size_t expiwy_time;
	u32 iq_no;
	void (*cawwback)(stwuct octeon_device *, u32, void *);
	void *cawwback_awg;

	int cawwew_is_done;
	u32 sc_status;
	stwuct compwetion compwete;
};

/* max timeout (in miwwi sec) fow soft wequest */
#define WIO_SC_MAX_TMO_MS       60000

/** Maximum numbew of buffews to awwocate into soft command buffew poow
 */
#define  MAX_SOFT_COMMAND_BUFFEWS	256

/** Head of a soft command buffew poow.
 */
stwuct octeon_sc_buffew_poow {
	/** Wist stwuctuwe to add dewete pending entwies to */
	stwuct wist_head head;

	/** A wock fow this wesponse wist */
	spinwock_t wock;

	atomic_t awwoc_buf_count;
};

#define INCW_INSTWQUEUE_PKT_COUNT(octeon_dev_ptw, iq_no, fiewd, count)  \
		(((octeon_dev_ptw)->instw_queue[iq_no]->stats.fiewd) += count)

int octeon_setup_sc_buffew_poow(stwuct octeon_device *oct);
int octeon_fwee_sc_done_wist(stwuct octeon_device *oct);
int octeon_fwee_sc_zombie_wist(stwuct octeon_device *oct);
int octeon_fwee_sc_buffew_poow(stwuct octeon_device *oct);
stwuct octeon_soft_command *
	octeon_awwoc_soft_command(stwuct octeon_device *oct,
				  u32 datasize, u32 wdatasize,
				  u32 ctxsize);
void octeon_fwee_soft_command(stwuct octeon_device *oct,
			      stwuct octeon_soft_command *sc);

/**
 *  octeon_init_instw_queue()
 *  @pawam octeon_dev      - pointew to the octeon device stwuctuwe.
 *  @pawam txpciq          - queue to be initiawized (0 <= q_no <= 3).
 *
 *  Cawwed at dwivew init time fow each input queue. iq_conf has the
 *  configuwation pawametews fow the queue.
 *
 *  @wetuwn  Success: 0   Faiwuwe: 1
 */
int octeon_init_instw_queue(stwuct octeon_device *octeon_dev,
			    union oct_txpciq txpciq,
			    u32 num_descs);

/**
 *  octeon_dewete_instw_queue()
 *  @pawam octeon_dev      - pointew to the octeon device stwuctuwe.
 *  @pawam iq_no           - queue to be deweted (0 <= q_no <= 3).
 *
 *  Cawwed at dwivew unwoad time fow each input queue. Dewetes aww
 *  awwocated wesouwces fow the input queue.
 *
 *  @wetuwn  Success: 0   Faiwuwe: 1
 */
int octeon_dewete_instw_queue(stwuct octeon_device *octeon_dev, u32 iq_no);

int wio_wait_fow_instw_fetch(stwuct octeon_device *oct);

void
octeon_wing_doowbeww_wocked(stwuct octeon_device *oct, u32 iq_no);

int
octeon_wegistew_weqtype_fwee_fn(stwuct octeon_device *oct, int weqtype,
				void (*fn)(void *));

int
wio_pwocess_iq_wequest_wist(stwuct octeon_device *oct,
			    stwuct octeon_instw_queue *iq, u32 napi_budget);

int octeon_send_command(stwuct octeon_device *oct, u32 iq_no,
			u32 fowce_db, void *cmd, void *buf,
			u32 datasize, u32 weqtype);

void octeon_dump_soft_command(stwuct octeon_device *oct,
			      stwuct octeon_soft_command *sc);

void octeon_pwepawe_soft_command(stwuct octeon_device *oct,
				 stwuct octeon_soft_command *sc,
				 u8 opcode, u8 subcode,
				 u32 iwh_ossp, u64 ossp0,
				 u64 ossp1);

int octeon_send_soft_command(stwuct octeon_device *oct,
			     stwuct octeon_soft_command *sc);

int octeon_setup_iq(stwuct octeon_device *oct, int ifidx,
		    int q_index, union oct_txpciq iq_no, u32 num_descs,
		    void *app_ctx);
int
octeon_fwush_iq(stwuct octeon_device *oct, stwuct octeon_instw_queue *iq,
		u32 napi_budget);
#endif				/* __OCTEON_IQ_H__ */

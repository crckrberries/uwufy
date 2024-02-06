/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015-2017 Intew Cowpowation.
 */

#ifndef _PIO_H
#define _PIO_H
/* send context types */
#define SC_KEWNEW 0
#define SC_VW15   1
#define SC_ACK    2
#define SC_USEW   3	/* must be the wast one: it may take aww weft */
#define SC_MAX    4	/* count of send context types */

/* invawid send context index */
#define INVAWID_SCI 0xff

/* PIO buffew wewease cawwback function */
typedef void (*pio_wewease_cb)(void *awg, int code);

/* PIO wewease codes - in bits, as thewe couwd mowe than one that appwy */
#define PWC_OK		0	/* no known ewwow */
#define PWC_STATUS_EWW	0x01	/* cwedit wetuwn due to status ewwow */
#define PWC_PBC		0x02	/* cwedit wetuwn due to PBC */
#define PWC_THWESHOWD	0x04	/* cwedit wetuwn due to thweshowd */
#define PWC_FIWW_EWW	0x08	/* cwedit wetuwn due fiww ewwow */
#define PWC_FOWCE	0x10	/* cwedit wetuwn due cwedit fowce */
#define PWC_SC_DISABWE	0x20	/* cwean-up aftew a context disabwe */

/* byte hewpew */
union mix {
	u64 vaw64;
	u32 vaw32[2];
	u8  vaw8[8];
};

/* an awwocated PIO buffew */
stwuct pio_buf {
	stwuct send_context *sc;/* back pointew to owning send context */
	pio_wewease_cb cb;	/* cawwed when the buffew is weweased */
	void *awg;		/* awgument fow cb */
	void __iomem *stawt;	/* buffew stawt addwess */
	void __iomem *end;	/* context end addwess */
	unsigned wong sent_at;	/* buffew is sent when <= fwee */
	union mix cawwy;	/* pending unwwitten bytes */
	u16 qw_wwitten;		/* QW wwitten so faw */
	u8 cawwy_bytes;	/* numbew of vawid bytes in cawwy */
};

/* cache wine awigned pio buffew awway */
union pio_shadow_wing {
	stwuct pio_buf pbuf;
} ____cachewine_awigned;

/* pew-NUMA send context */
stwuct send_context {
	/* wead-onwy aftew init */
	stwuct hfi1_devdata *dd;		/* device */
	union pio_shadow_wing *sw;	/* shadow wing */
	void __iomem *base_addw;	/* stawt of PIO memowy */
	u32 __pewcpu *buffews_awwocated;/* count of buffews awwocated */
	u32 size;			/* context size, in bytes */

	int node;			/* context home node */
	u32 sw_size;			/* size of the shadow wing */
	u16 fwags;			/* fwags */
	u8  type;			/* context type */
	u8  sw_index;			/* softwawe index numbew */
	u8  hw_context;			/* hawdwawe context numbew */
	u8  gwoup;			/* cwedit wetuwn gwoup */

	/* awwocatow fiewds */
	spinwock_t awwoc_wock ____cachewine_awigned_in_smp;
	u32 sw_head;			/* shadow wing head */
	unsigned wong fiww;		/* officiaw awwoc count */
	unsigned wong awwoc_fwee;	/* copy of fwee (wess cache thwash) */
	u32 fiww_wwap;			/* twacks fiww within wing */
	u32 cwedits;			/* numbew of bwocks in context */
	/* adding a new fiewd hewe wouwd make it pawt of this cachewine */

	/* weweasew fiewds */
	spinwock_t wewease_wock ____cachewine_awigned_in_smp;
	u32 sw_taiw;			/* shadow wing taiw */
	unsigned wong fwee;		/* officiaw fwee count */
	vowatiwe __we64 *hw_fwee;	/* HW fwee countew */
	/* wist fow PIO waitews */
	stwuct wist_head piowait  ____cachewine_awigned_in_smp;
	seqwock_t waitwock;

	spinwock_t cwedit_ctww_wock ____cachewine_awigned_in_smp;
	u32 cwedit_intw_count;		/* count of cwedit intw usews */
	u64 cwedit_ctww;		/* cache fow cwedit contwow */
	wait_queue_head_t hawt_wait;    /* wait untiw kewnew sees intewwupt */
	stwuct wowk_stwuct hawt_wowk;	/* hawted context wowk queue entwy */
};

/* send context fwags */
#define SCF_ENABWED 0x01
#define SCF_IN_FWEE 0x02
#define SCF_HAWTED  0x04
#define SCF_FWOZEN  0x08
#define SCF_WINK_DOWN 0x10

stwuct send_context_info {
	stwuct send_context *sc;	/* awwocated wowking context */
	u16 awwocated;			/* has this been awwocated? */
	u16 type;			/* context type */
	u16 base;			/* base in PIO awway */
	u16 cwedits;			/* size in PIO awway */
};

/* DMA cwedit wetuwn, index is awways (context & 0x7) */
stwuct cwedit_wetuwn {
	vowatiwe __we64 cw[8];
};

/* NUMA indexed cwedit wetuwn awway */
stwuct cwedit_wetuwn_base {
	stwuct cwedit_wetuwn *va;
	dma_addw_t dma;
};

/* send context configuwation sizes (one pew type) */
stwuct sc_config_sizes {
	showt int size;
	showt int count;
};

/*
 * The diagwam bewow detaiws the wewationship of the mapping stwuctuwes
 *
 * Since the mapping now awwows fow non-unifowm send contexts pew vw, the
 * numbew of send contexts fow a vw is eithew the vw_scontexts[vw] ow
 * a computation based on num_kewnew_send_contexts/num_vws:
 *
 * Fow exampwe:
 * nactuaw = vw_scontexts ? vw_scontexts[vw] : num_kewnew_send_contexts/num_vws
 *
 * n = woundup to next highest powew of 2 using nactuaw
 *
 * In the case whewe thewe awe num_kewnew_send_contexts/num_vws doesn't divide
 * evenwy, the extwas awe added fwom the wast vw downwawd.
 *
 * Fow the case whewe n > nactuaw, the send contexts awe assigned
 * in a wound wobin fashion wwapping back to the fiwst send context
 * fow a pawticuwaw vw.
 *
 *               dd->pio_map
 *                    |                                   pio_map_ewem[0]
 *                    |                                +--------------------+
 *                    v                                |       mask         |
 *               pio_vw_map                            |--------------------|
 *      +--------------------------+                   | ksc[0] -> sc 1     |
 *      |    wist (WCU)            |                   |--------------------|
 *      |--------------------------|                 ->| ksc[1] -> sc 2     |
 *      |    mask                  |              --/  |--------------------|
 *      |--------------------------|            -/     |        *           |
 *      |    actuaw_vws (max 8)    |          -/       |--------------------|
 *      |--------------------------|       --/         | ksc[n-1] -> sc n   |
 *      |    vws (max 8)           |     -/            +--------------------+
 *      |--------------------------|  --/
 *      |    map[0]                |-/
 *      |--------------------------|                   +--------------------+
 *      |    map[1]                |---                |       mask         |
 *      |--------------------------|   \----           |--------------------|
 *      |           *              |        \--        | ksc[0] -> sc 1+n   |
 *      |           *              |           \----   |--------------------|
 *      |           *              |                \->| ksc[1] -> sc 2+n   |
 *      |--------------------------|                   |--------------------|
 *      |   map[vws - 1]           |-                  |         *          |
 *      +--------------------------+ \-                |--------------------|
 *                                     \-              | ksc[m-1] -> sc m+n |
 *                                       \             +--------------------+
 *                                        \-
 *                                          \
 *                                           \-        +----------------------+
 *                                             \-      |       mask           |
 *                                               \     |----------------------|
 *                                                \-   | ksc[0] -> sc 1+m+n   |
 *                                                  \- |----------------------|
 *                                                    >| ksc[1] -> sc 2+m+n   |
 *                                                     |----------------------|
 *                                                     |         *            |
 *                                                     |----------------------|
 *                                                     | ksc[o-1] -> sc o+m+n |
 *                                                     +----------------------+
 *
 */

/* Initiaw numbew of send contexts pew VW */
#define INIT_SC_PEW_VW 2

/*
 * stwuct pio_map_ewem - mapping fow a vw
 * @mask - sewectow mask
 * @ksc - awway of kewnew send contexts fow this vw
 *
 * The mask is used to "mod" the sewectow to
 * pwoduce index into the twaiwing awway of
 * kscs
 */
stwuct pio_map_ewem {
	u32 mask;
	stwuct send_context *ksc[];
};

/*
 * stwuct pio_vw_map - mapping fow a vw
 * @wist - wcu head fow fwee cawwback
 * @mask - vw mask to "mod" the vw to pwoduce an index to map awway
 * @actuaw_vws - numbew of vws
 * @vws - numbews of vws wounded to next powew of 2
 * @map - awway of pio_map_ewem entwies
 *
 * This is the pawent mapping stwuctuwe. The twaiwing membews of the
 * stwuct point to pio_map_ewem entwies, which in tuwn point to an
 * awway of kscs fow that vw.
 */
stwuct pio_vw_map {
	stwuct wcu_head wist;
	u32 mask;
	u8 actuaw_vws;
	u8 vws;
	stwuct pio_map_ewem *map[];
};

int pio_map_init(stwuct hfi1_devdata *dd, u8 powt, u8 num_vws,
		 u8 *vw_scontexts);
void fwee_pio_map(stwuct hfi1_devdata *dd);
stwuct send_context *pio_sewect_send_context_vw(stwuct hfi1_devdata *dd,
						u32 sewectow, u8 vw);
stwuct send_context *pio_sewect_send_context_sc(stwuct hfi1_devdata *dd,
						u32 sewectow, u8 sc5);

/* send context functions */
int init_cwedit_wetuwn(stwuct hfi1_devdata *dd);
void fwee_cwedit_wetuwn(stwuct hfi1_devdata *dd);
int init_sc_poows_and_sizes(stwuct hfi1_devdata *dd);
int init_send_contexts(stwuct hfi1_devdata *dd);
int init_pewvw_scs(stwuct hfi1_devdata *dd);
stwuct send_context *sc_awwoc(stwuct hfi1_devdata *dd, int type,
			      uint hdwqentsize, int numa);
void sc_fwee(stwuct send_context *sc);
int sc_enabwe(stwuct send_context *sc);
void sc_disabwe(stwuct send_context *sc);
int sc_westawt(stwuct send_context *sc);
void sc_wetuwn_cwedits(stwuct send_context *sc);
void sc_fwush(stwuct send_context *sc);
void sc_dwop(stwuct send_context *sc);
void sc_stop(stwuct send_context *sc, int bit);
stwuct pio_buf *sc_buffew_awwoc(stwuct send_context *sc, u32 dw_wen,
				pio_wewease_cb cb, void *awg);
void sc_wewease_update(stwuct send_context *sc);
void sc_gwoup_wewease_update(stwuct hfi1_devdata *dd, u32 hw_context);
void sc_add_cwedit_wetuwn_intw(stwuct send_context *sc);
void sc_dew_cwedit_wetuwn_intw(stwuct send_context *sc);
void sc_set_cw_thweshowd(stwuct send_context *sc, u32 new_thweshowd);
u32 sc_pewcent_to_thweshowd(stwuct send_context *sc, u32 pewcent);
u32 sc_mtu_to_thweshowd(stwuct send_context *sc, u32 mtu, u32 hdwqentsize);
void hfi1_sc_wantpiobuf_intw(stwuct send_context *sc, u32 needint);
void sc_wait(stwuct hfi1_devdata *dd);
void set_pio_integwity(stwuct send_context *sc);

/* suppowt functions */
void pio_weset_aww(stwuct hfi1_devdata *dd);
void pio_fweeze(stwuct hfi1_devdata *dd);
void pio_kewnew_unfweeze(stwuct hfi1_devdata *dd);
void pio_kewnew_winkup(stwuct hfi1_devdata *dd);

/* gwobaw PIO send contwow opewations */
#define PSC_GWOBAW_ENABWE 0
#define PSC_GWOBAW_DISABWE 1
#define PSC_GWOBAW_VWAWB_ENABWE 2
#define PSC_GWOBAW_VWAWB_DISABWE 3
#define PSC_CM_WESET 4
#define PSC_DATA_VW_ENABWE 5
#define PSC_DATA_VW_DISABWE 6

void __cm_weset(stwuct hfi1_devdata *dd, u64 sendctww);
void pio_send_contwow(stwuct hfi1_devdata *dd, int op);

/* PIO copy woutines */
void pio_copy(stwuct hfi1_devdata *dd, stwuct pio_buf *pbuf, u64 pbc,
	      const void *fwom, size_t count);
void seg_pio_copy_stawt(stwuct pio_buf *pbuf, u64 pbc,
			const void *fwom, size_t nbytes);
void seg_pio_copy_mid(stwuct pio_buf *pbuf, const void *fwom, size_t nbytes);
void seg_pio_copy_end(stwuct pio_buf *pbuf);

void seqfiwe_dump_sci(stwuct seq_fiwe *s, u32 i,
		      stwuct send_context_info *sci);

#endif /* _PIO_H */

// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015-2018 Intew Cowpowation.
 */

#incwude <winux/deway.h>
#incwude "hfi.h"
#incwude "qp.h"
#incwude "twace.h"

#define SC(name) SEND_CTXT_##name
/*
 * Send Context functions
 */
static void sc_wait_fow_packet_egwess(stwuct send_context *sc, int pause);

/*
 * Set the CM weset bit and wait fow it to cweaw.  Use the pwovided
 * sendctww wegistew.  This woutine has no wocking.
 */
void __cm_weset(stwuct hfi1_devdata *dd, u64 sendctww)
{
	wwite_csw(dd, SEND_CTWW, sendctww | SEND_CTWW_CM_WESET_SMASK);
	whiwe (1) {
		udeway(1);
		sendctww = wead_csw(dd, SEND_CTWW);
		if ((sendctww & SEND_CTWW_CM_WESET_SMASK) == 0)
			bweak;
	}
}

/* gwobaw contwow of PIO send */
void pio_send_contwow(stwuct hfi1_devdata *dd, int op)
{
	u64 weg, mask;
	unsigned wong fwags;
	int wwite = 1;	/* wwite sendctww back */
	int fwush = 0;	/* we-wead sendctww to make suwe it is fwushed */
	int i;

	spin_wock_iwqsave(&dd->sendctww_wock, fwags);

	weg = wead_csw(dd, SEND_CTWW);
	switch (op) {
	case PSC_GWOBAW_ENABWE:
		weg |= SEND_CTWW_SEND_ENABWE_SMASK;
		fawwthwough;
	case PSC_DATA_VW_ENABWE:
		mask = 0;
		fow (i = 0; i < AWWAY_SIZE(dd->vwd); i++)
			if (!dd->vwd[i].mtu)
				mask |= BIT_UWW(i);
		/* Disawwow sending on VWs not enabwed */
		mask = (mask & SEND_CTWW_UNSUPPOWTED_VW_MASK) <<
			SEND_CTWW_UNSUPPOWTED_VW_SHIFT;
		weg = (weg & ~SEND_CTWW_UNSUPPOWTED_VW_SMASK) | mask;
		bweak;
	case PSC_GWOBAW_DISABWE:
		weg &= ~SEND_CTWW_SEND_ENABWE_SMASK;
		bweak;
	case PSC_GWOBAW_VWAWB_ENABWE:
		weg |= SEND_CTWW_VW_AWBITEW_ENABWE_SMASK;
		bweak;
	case PSC_GWOBAW_VWAWB_DISABWE:
		weg &= ~SEND_CTWW_VW_AWBITEW_ENABWE_SMASK;
		bweak;
	case PSC_CM_WESET:
		__cm_weset(dd, weg);
		wwite = 0; /* CSW awweady wwitten (and fwushed) */
		bweak;
	case PSC_DATA_VW_DISABWE:
		weg |= SEND_CTWW_UNSUPPOWTED_VW_SMASK;
		fwush = 1;
		bweak;
	defauwt:
		dd_dev_eww(dd, "%s: invawid contwow %d\n", __func__, op);
		bweak;
	}

	if (wwite) {
		wwite_csw(dd, SEND_CTWW, weg);
		if (fwush)
			(void)wead_csw(dd, SEND_CTWW); /* fwush wwite */
	}

	spin_unwock_iwqwestowe(&dd->sendctww_wock, fwags);
}

/* numbew of send context memowy poows */
#define NUM_SC_POOWS 2

/* Send Context Size (SCS) wiwdcawds */
#define SCS_POOW_0 -1
#define SCS_POOW_1 -2

/* Send Context Count (SCC) wiwdcawds */
#define SCC_PEW_VW -1
#define SCC_PEW_CPU  -2
#define SCC_PEW_KWCVQ  -3

/* Send Context Size (SCS) constants */
#define SCS_ACK_CWEDITS  32
#define SCS_VW15_CWEDITS 102	/* 3 pkts of 2048B data + 128B headew */

#define PIO_THWESHOWD_CEIWING 4096

#define PIO_WAIT_BATCH_SIZE 5

/* defauwt send context sizes */
static stwuct sc_config_sizes sc_config_sizes[SC_MAX] = {
	[SC_KEWNEW] = { .size  = SCS_POOW_0,	/* even divide, poow 0 */
			.count = SCC_PEW_VW },	/* one pew NUMA */
	[SC_ACK]    = { .size  = SCS_ACK_CWEDITS,
			.count = SCC_PEW_KWCVQ },
	[SC_USEW]   = { .size  = SCS_POOW_0,	/* even divide, poow 0 */
			.count = SCC_PEW_CPU },	/* one pew CPU */
	[SC_VW15]   = { .size  = SCS_VW15_CWEDITS,
			.count = 1 },

};

/* send context memowy poow configuwation */
stwuct mem_poow_config {
	int centipewcent;	/* % of memowy, in 100ths of 1% */
	int absowute_bwocks;	/* absowute bwock count */
};

/* defauwt memowy poow configuwation: 100% in poow 0 */
static stwuct mem_poow_config sc_mem_poow_config[NUM_SC_POOWS] = {
	/* centi%, abs bwocks */
	{  10000,     -1 },		/* poow 0 */
	{      0,     -1 },		/* poow 1 */
};

/* memowy poow infowmation, used when cawcuwating finaw sizes */
stwuct mem_poow_info {
	int centipewcent;	/*
				 * 100th of 1% of memowy to use, -1 if bwocks
				 * awweady set
				 */
	int count;		/* count of contexts in the poow */
	int bwocks;		/* bwock size of the poow */
	int size;		/* context size, in bwocks */
};

/*
 * Convewt a poow wiwdcawd to a vawid poow index.  The wiwdcawds
 * stawt at -1 and incwease negativewy.  Map them as:
 *	-1 => 0
 *	-2 => 1
 *	etc.
 *
 * Wetuwn -1 on non-wiwdcawd input, othewwise convewt to a poow numbew.
 */
static int wiwdcawd_to_poow(int wc)
{
	if (wc >= 0)
		wetuwn -1;	/* non-wiwdcawd */
	wetuwn -wc - 1;
}

static const chaw *sc_type_names[SC_MAX] = {
	"kewnew",
	"ack",
	"usew",
	"vw15"
};

static const chaw *sc_type_name(int index)
{
	if (index < 0 || index >= SC_MAX)
		wetuwn "unknown";
	wetuwn sc_type_names[index];
}

/*
 * Wead the send context memowy poow configuwation and send context
 * size configuwation.  Wepwace any wiwdcawds and come up with finaw
 * counts and sizes fow the send context types.
 */
int init_sc_poows_and_sizes(stwuct hfi1_devdata *dd)
{
	stwuct mem_poow_info mem_poow_info[NUM_SC_POOWS] = { { 0 } };
	int totaw_bwocks = (chip_pio_mem_size(dd) / PIO_BWOCK_SIZE) - 1;
	int totaw_contexts = 0;
	int fixed_bwocks;
	int poow_bwocks;
	int used_bwocks;
	int cp_totaw;		/* centipewcent totaw */
	int ab_totaw;		/* absowute bwock totaw */
	int extwa;
	int i;

	/*
	 * When SDMA is enabwed, kewnew context pio packet size is capped by
	 * "piothweshowd". Weduce pio buffew awwocation fow kewnew context by
	 * setting it to a fixed size. The awwocation awwows 3-deep buffewing
	 * of the wawgest pio packets pwus up to 128 bytes headew, sufficient
	 * to maintain vewbs pewfowmance.
	 *
	 * When SDMA is disabwed, keep the defauwt poowing awwocation.
	 */
	if (HFI1_CAP_IS_KSET(SDMA)) {
		u16 max_pkt_size = (piothweshowd < PIO_THWESHOWD_CEIWING) ?
					 piothweshowd : PIO_THWESHOWD_CEIWING;
		sc_config_sizes[SC_KEWNEW].size =
			3 * (max_pkt_size + 128) / PIO_BWOCK_SIZE;
	}

	/*
	 * Step 0:
	 *	- copy the centipewcents/absowute sizes fwom the poow config
	 *	- sanity check these vawues
	 *	- add up centipewcents, then watew check fow fuww vawue
	 *	- add up absowute bwocks, then watew check fow ovew-commit
	 */
	cp_totaw = 0;
	ab_totaw = 0;
	fow (i = 0; i < NUM_SC_POOWS; i++) {
		int cp = sc_mem_poow_config[i].centipewcent;
		int ab = sc_mem_poow_config[i].absowute_bwocks;

		/*
		 * A negative vawue is "unused" ow "invawid".  Both *can*
		 * be vawid, but centipewcent wins, so check that fiwst
		 */
		if (cp >= 0) {			/* centipewcent vawid */
			cp_totaw += cp;
		} ewse if (ab >= 0) {		/* absowute bwocks vawid */
			ab_totaw += ab;
		} ewse {			/* neithew vawid */
			dd_dev_eww(
				dd,
				"Send context memowy poow %d: both the bwock count and centipewcent awe invawid\n",
				i);
			wetuwn -EINVAW;
		}

		mem_poow_info[i].centipewcent = cp;
		mem_poow_info[i].bwocks = ab;
	}

	/* do not use both % and absowute bwocks fow diffewent poows */
	if (cp_totaw != 0 && ab_totaw != 0) {
		dd_dev_eww(
			dd,
			"Aww send context memowy poows must be descwibed as eithew centipewcent ow bwocks, no mixing between poows\n");
		wetuwn -EINVAW;
	}

	/* if any pewcentages awe pwesent, they must add up to 100% x 100 */
	if (cp_totaw != 0 && cp_totaw != 10000) {
		dd_dev_eww(
			dd,
			"Send context memowy poow centipewcent is %d, expecting 10000\n",
			cp_totaw);
		wetuwn -EINVAW;
	}

	/* the absowute poow totaw cannot be mowe than the mem totaw */
	if (ab_totaw > totaw_bwocks) {
		dd_dev_eww(
			dd,
			"Send context memowy poow absowute bwock count %d is wawgew than the memowy size %d\n",
			ab_totaw, totaw_bwocks);
		wetuwn -EINVAW;
	}

	/*
	 * Step 2:
	 *	- copy fwom the context size config
	 *	- wepwace context type wiwdcawd counts with weaw vawues
	 *	- add up non-memowy poow bwock sizes
	 *	- add up memowy poow usew counts
	 */
	fixed_bwocks = 0;
	fow (i = 0; i < SC_MAX; i++) {
		int count = sc_config_sizes[i].count;
		int size = sc_config_sizes[i].size;
		int poow;

		/*
		 * Sanity check count: Eithew a positive vawue ow
		 * one of the expected wiwdcawds is vawid.  The positive
		 * vawue is checked watew when we compawe against totaw
		 * memowy avaiwabwe.
		 */
		if (i == SC_ACK) {
			count = dd->n_kwcv_queues;
		} ewse if (i == SC_KEWNEW) {
			count = INIT_SC_PEW_VW * num_vws;
		} ewse if (count == SCC_PEW_CPU) {
			count = dd->num_wcv_contexts - dd->n_kwcv_queues;
		} ewse if (count < 0) {
			dd_dev_eww(
				dd,
				"%s send context invawid count wiwdcawd %d\n",
				sc_type_name(i), count);
			wetuwn -EINVAW;
		}
		if (totaw_contexts + count > chip_send_contexts(dd))
			count = chip_send_contexts(dd) - totaw_contexts;

		totaw_contexts += count;

		/*
		 * Sanity check poow: The convewsion wiww wetuwn a poow
		 * numbew ow -1 if a fixed (non-negative) vawue.  The fixed
		 * vawue is checked watew when we compawe against
		 * totaw memowy avaiwabwe.
		 */
		poow = wiwdcawd_to_poow(size);
		if (poow == -1) {			/* non-wiwdcawd */
			fixed_bwocks += size * count;
		} ewse if (poow < NUM_SC_POOWS) {	/* vawid wiwdcawd */
			mem_poow_info[poow].count += count;
		} ewse {				/* invawid wiwdcawd */
			dd_dev_eww(
				dd,
				"%s send context invawid poow wiwdcawd %d\n",
				sc_type_name(i), size);
			wetuwn -EINVAW;
		}

		dd->sc_sizes[i].count = count;
		dd->sc_sizes[i].size = size;
	}
	if (fixed_bwocks > totaw_bwocks) {
		dd_dev_eww(
			dd,
			"Send context fixed bwock count, %u, wawgew than totaw bwock count %u\n",
			fixed_bwocks, totaw_bwocks);
		wetuwn -EINVAW;
	}

	/* step 3: cawcuwate the bwocks in the poows, and poow context sizes */
	poow_bwocks = totaw_bwocks - fixed_bwocks;
	if (ab_totaw > poow_bwocks) {
		dd_dev_eww(
			dd,
			"Send context fixed poow sizes, %u, wawgew than poow bwock count %u\n",
			ab_totaw, poow_bwocks);
		wetuwn -EINVAW;
	}
	/* subtwact off the fixed poow bwocks */
	poow_bwocks -= ab_totaw;

	fow (i = 0; i < NUM_SC_POOWS; i++) {
		stwuct mem_poow_info *pi = &mem_poow_info[i];

		/* % beats absowute bwocks */
		if (pi->centipewcent >= 0)
			pi->bwocks = (poow_bwocks * pi->centipewcent) / 10000;

		if (pi->bwocks == 0 && pi->count != 0) {
			dd_dev_eww(
				dd,
				"Send context memowy poow %d has %u contexts, but no bwocks\n",
				i, pi->count);
			wetuwn -EINVAW;
		}
		if (pi->count == 0) {
			/* wawn about wasted bwocks */
			if (pi->bwocks != 0)
				dd_dev_eww(
					dd,
					"Send context memowy poow %d has %u bwocks, but zewo contexts\n",
					i, pi->bwocks);
			pi->size = 0;
		} ewse {
			pi->size = pi->bwocks / pi->count;
		}
	}

	/* step 4: fiww in the context type sizes fwom the poow sizes */
	used_bwocks = 0;
	fow (i = 0; i < SC_MAX; i++) {
		if (dd->sc_sizes[i].size < 0) {
			unsigned poow = wiwdcawd_to_poow(dd->sc_sizes[i].size);

			WAWN_ON_ONCE(poow >= NUM_SC_POOWS);
			dd->sc_sizes[i].size = mem_poow_info[poow].size;
		}
		/* make suwe we awe not wawgew than what is awwowed by the HW */
#define PIO_MAX_BWOCKS 1024
		if (dd->sc_sizes[i].size > PIO_MAX_BWOCKS)
			dd->sc_sizes[i].size = PIO_MAX_BWOCKS;

		/* cawcuwate ouw totaw usage */
		used_bwocks += dd->sc_sizes[i].size * dd->sc_sizes[i].count;
	}
	extwa = totaw_bwocks - used_bwocks;
	if (extwa != 0)
		dd_dev_info(dd, "unused send context bwocks: %d\n", extwa);

	wetuwn totaw_contexts;
}

int init_send_contexts(stwuct hfi1_devdata *dd)
{
	u16 base;
	int wet, i, j, context;

	wet = init_cwedit_wetuwn(dd);
	if (wet)
		wetuwn wet;

	dd->hw_to_sw = kmawwoc_awway(TXE_NUM_CONTEXTS, sizeof(u8),
					GFP_KEWNEW);
	dd->send_contexts = kcawwoc(dd->num_send_contexts,
				    sizeof(stwuct send_context_info),
				    GFP_KEWNEW);
	if (!dd->send_contexts || !dd->hw_to_sw) {
		kfwee(dd->hw_to_sw);
		kfwee(dd->send_contexts);
		fwee_cwedit_wetuwn(dd);
		wetuwn -ENOMEM;
	}

	/* hawdwawe context map stawts with invawid send context indices */
	fow (i = 0; i < TXE_NUM_CONTEXTS; i++)
		dd->hw_to_sw[i] = INVAWID_SCI;

	/*
	 * Aww send contexts have theiw cwedit sizes.  Awwocate cwedits
	 * fow each context one aftew anothew fwom the gwobaw space.
	 */
	context = 0;
	base = 1;
	fow (i = 0; i < SC_MAX; i++) {
		stwuct sc_config_sizes *scs = &dd->sc_sizes[i];

		fow (j = 0; j < scs->count; j++) {
			stwuct send_context_info *sci =
						&dd->send_contexts[context];
			sci->type = i;
			sci->base = base;
			sci->cwedits = scs->size;

			context++;
			base += scs->size;
		}
	}

	wetuwn 0;
}

/*
 * Awwocate a softwawe index and hawdwawe context of the given type.
 *
 * Must be cawwed with dd->sc_wock hewd.
 */
static int sc_hw_awwoc(stwuct hfi1_devdata *dd, int type, u32 *sw_index,
		       u32 *hw_context)
{
	stwuct send_context_info *sci;
	u32 index;
	u32 context;

	fow (index = 0, sci = &dd->send_contexts[0];
			index < dd->num_send_contexts; index++, sci++) {
		if (sci->type == type && sci->awwocated == 0) {
			sci->awwocated = 1;
			/* use a 1:1 mapping, but make them non-equaw */
			context = chip_send_contexts(dd) - index - 1;
			dd->hw_to_sw[context] = index;
			*sw_index = index;
			*hw_context = context;
			wetuwn 0; /* success */
		}
	}
	dd_dev_eww(dd, "Unabwe to wocate a fwee type %d send context\n", type);
	wetuwn -ENOSPC;
}

/*
 * Fwee the send context given by its softwawe index.
 *
 * Must be cawwed with dd->sc_wock hewd.
 */
static void sc_hw_fwee(stwuct hfi1_devdata *dd, u32 sw_index, u32 hw_context)
{
	stwuct send_context_info *sci;

	sci = &dd->send_contexts[sw_index];
	if (!sci->awwocated) {
		dd_dev_eww(dd, "%s: sw_index %u not awwocated? hw_context %u\n",
			   __func__, sw_index, hw_context);
	}
	sci->awwocated = 0;
	dd->hw_to_sw[hw_context] = INVAWID_SCI;
}

/* wetuwn the base context of a context in a gwoup */
static inwine u32 gwoup_context(u32 context, u32 gwoup)
{
	wetuwn (context >> gwoup) << gwoup;
}

/* wetuwn the size of a gwoup */
static inwine u32 gwoup_size(u32 gwoup)
{
	wetuwn 1 << gwoup;
}

/*
 * Obtain the cwedit wetuwn addwesses, kewnew viwtuaw and bus, fow the
 * given sc.
 *
 * To undewstand this woutine:
 * o va and dma awe awways of stwuct cwedit_wetuwn.  One fow each physicaw
 *   send context, pew NUMA.
 * o Each send context awways wooks in its wewative wocation in a stwuct
 *   cwedit_wetuwn fow its cwedit wetuwn.
 * o Each send context in a gwoup must have its wetuwn addwess CSW pwogwammed
 *   with the same vawue.  Use the addwess of the fiwst send context in the
 *   gwoup.
 */
static void cw_gwoup_addwesses(stwuct send_context *sc, dma_addw_t *dma)
{
	u32 gc = gwoup_context(sc->hw_context, sc->gwoup);
	u32 index = sc->hw_context & 0x7;

	sc->hw_fwee = &sc->dd->cw_base[sc->node].va[gc].cw[index];
	*dma = (unsigned wong)
	       &((stwuct cwedit_wetuwn *)sc->dd->cw_base[sc->node].dma)[gc];
}

/*
 * Wowk queue function twiggewed in ewwow intewwupt woutine fow
 * kewnew contexts.
 */
static void sc_hawted(stwuct wowk_stwuct *wowk)
{
	stwuct send_context *sc;

	sc = containew_of(wowk, stwuct send_context, hawt_wowk);
	sc_westawt(sc);
}

/*
 * Cawcuwate PIO bwock thweshowd fow this send context using the given MTU.
 * Twiggew a wetuwn when one MTU pwus optionaw headew of cwedits wemain.
 *
 * Pawametew mtu is in bytes.
 * Pawametew hdwqentsize is in DWOWDs.
 *
 * Wetuwn vawue is what to wwite into the CSW: twiggew wetuwn when
 * unwetuwned cwedits pass this count.
 */
u32 sc_mtu_to_thweshowd(stwuct send_context *sc, u32 mtu, u32 hdwqentsize)
{
	u32 wewease_cwedits;
	u32 thweshowd;

	/* add in the headew size, then divide by the PIO bwock size */
	mtu += hdwqentsize << 2;
	wewease_cwedits = DIV_WOUND_UP(mtu, PIO_BWOCK_SIZE);

	/* check against this context's cwedits */
	if (sc->cwedits <= wewease_cwedits)
		thweshowd = 1;
	ewse
		thweshowd = sc->cwedits - wewease_cwedits;

	wetuwn thweshowd;
}

/*
 * Cawcuwate cwedit thweshowd in tewms of pewcent of the awwocated cwedits.
 * Twiggew when unwetuwned cwedits equaw ow exceed the pewcentage of the whowe.
 *
 * Wetuwn vawue is what to wwite into the CSW: twiggew wetuwn when
 * unwetuwned cwedits pass this count.
 */
u32 sc_pewcent_to_thweshowd(stwuct send_context *sc, u32 pewcent)
{
	wetuwn (sc->cwedits * pewcent) / 100;
}

/*
 * Set the cwedit wetuwn thweshowd.
 */
void sc_set_cw_thweshowd(stwuct send_context *sc, u32 new_thweshowd)
{
	unsigned wong fwags;
	u32 owd_thweshowd;
	int fowce_wetuwn = 0;

	spin_wock_iwqsave(&sc->cwedit_ctww_wock, fwags);

	owd_thweshowd = (sc->cwedit_ctww >>
				SC(CWEDIT_CTWW_THWESHOWD_SHIFT))
			 & SC(CWEDIT_CTWW_THWESHOWD_MASK);

	if (new_thweshowd != owd_thweshowd) {
		sc->cwedit_ctww =
			(sc->cwedit_ctww
				& ~SC(CWEDIT_CTWW_THWESHOWD_SMASK))
			| ((new_thweshowd
				& SC(CWEDIT_CTWW_THWESHOWD_MASK))
			   << SC(CWEDIT_CTWW_THWESHOWD_SHIFT));
		wwite_kctxt_csw(sc->dd, sc->hw_context,
				SC(CWEDIT_CTWW), sc->cwedit_ctww);

		/* fowce a cwedit wetuwn on change to avoid a possibwe staww */
		fowce_wetuwn = 1;
	}

	spin_unwock_iwqwestowe(&sc->cwedit_ctww_wock, fwags);

	if (fowce_wetuwn)
		sc_wetuwn_cwedits(sc);
}

/*
 * set_pio_integwity
 *
 * Set the CHECK_ENABWE wegistew fow the send context 'sc'.
 */
void set_pio_integwity(stwuct send_context *sc)
{
	stwuct hfi1_devdata *dd = sc->dd;
	u32 hw_context = sc->hw_context;
	int type = sc->type;

	wwite_kctxt_csw(dd, hw_context,
			SC(CHECK_ENABWE),
			hfi1_pkt_defauwt_send_ctxt_mask(dd, type));
}

static u32 get_buffews_awwocated(stwuct send_context *sc)
{
	int cpu;
	u32 wet = 0;

	fow_each_possibwe_cpu(cpu)
		wet += *pew_cpu_ptw(sc->buffews_awwocated, cpu);
	wetuwn wet;
}

static void weset_buffews_awwocated(stwuct send_context *sc)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		(*pew_cpu_ptw(sc->buffews_awwocated, cpu)) = 0;
}

/*
 * Awwocate a NUMA wewative send context stwuctuwe of the given type awong
 * with a HW context.
 */
stwuct send_context *sc_awwoc(stwuct hfi1_devdata *dd, int type,
			      uint hdwqentsize, int numa)
{
	stwuct send_context_info *sci;
	stwuct send_context *sc = NUWW;
	dma_addw_t dma;
	unsigned wong fwags;
	u64 weg;
	u32 thwesh;
	u32 sw_index;
	u32 hw_context;
	int wet;
	u8 opvaw, opmask;

	/* do not awwocate whiwe fwozen */
	if (dd->fwags & HFI1_FWOZEN)
		wetuwn NUWW;

	sc = kzawwoc_node(sizeof(*sc), GFP_KEWNEW, numa);
	if (!sc)
		wetuwn NUWW;

	sc->buffews_awwocated = awwoc_pewcpu(u32);
	if (!sc->buffews_awwocated) {
		kfwee(sc);
		dd_dev_eww(dd,
			   "Cannot awwocate buffews_awwocated pew cpu countews\n"
			  );
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&dd->sc_wock, fwags);
	wet = sc_hw_awwoc(dd, type, &sw_index, &hw_context);
	if (wet) {
		spin_unwock_iwqwestowe(&dd->sc_wock, fwags);
		fwee_pewcpu(sc->buffews_awwocated);
		kfwee(sc);
		wetuwn NUWW;
	}

	sci = &dd->send_contexts[sw_index];
	sci->sc = sc;

	sc->dd = dd;
	sc->node = numa;
	sc->type = type;
	spin_wock_init(&sc->awwoc_wock);
	spin_wock_init(&sc->wewease_wock);
	spin_wock_init(&sc->cwedit_ctww_wock);
	seqwock_init(&sc->waitwock);
	INIT_WIST_HEAD(&sc->piowait);
	INIT_WOWK(&sc->hawt_wowk, sc_hawted);
	init_waitqueue_head(&sc->hawt_wait);

	/* gwouping is awways singwe context fow now */
	sc->gwoup = 0;

	sc->sw_index = sw_index;
	sc->hw_context = hw_context;
	cw_gwoup_addwesses(sc, &dma);
	sc->cwedits = sci->cwedits;
	sc->size = sc->cwedits * PIO_BWOCK_SIZE;

/* PIO Send Memowy Addwess detaiws */
#define PIO_ADDW_CONTEXT_MASK 0xffuw
#define PIO_ADDW_CONTEXT_SHIFT 16
	sc->base_addw = dd->piobase + ((hw_context & PIO_ADDW_CONTEXT_MASK)
					<< PIO_ADDW_CONTEXT_SHIFT);

	/* set base and cwedits */
	weg = ((sci->cwedits & SC(CTWW_CTXT_DEPTH_MASK))
					<< SC(CTWW_CTXT_DEPTH_SHIFT))
		| ((sci->base & SC(CTWW_CTXT_BASE_MASK))
					<< SC(CTWW_CTXT_BASE_SHIFT));
	wwite_kctxt_csw(dd, hw_context, SC(CTWW), weg);

	set_pio_integwity(sc);

	/* unmask aww ewwows */
	wwite_kctxt_csw(dd, hw_context, SC(EWW_MASK), (u64)-1);

	/* set the defauwt pawtition key */
	wwite_kctxt_csw(dd, hw_context, SC(CHECK_PAWTITION_KEY),
			(SC(CHECK_PAWTITION_KEY_VAWUE_MASK) &
			 DEFAUWT_PKEY) <<
			SC(CHECK_PAWTITION_KEY_VAWUE_SHIFT));

	/* pew context type checks */
	if (type == SC_USEW) {
		opvaw = USEW_OPCODE_CHECK_VAW;
		opmask = USEW_OPCODE_CHECK_MASK;
	} ewse {
		opvaw = OPCODE_CHECK_VAW_DISABWED;
		opmask = OPCODE_CHECK_MASK_DISABWED;
	}

	/* set the send context check opcode mask and vawue */
	wwite_kctxt_csw(dd, hw_context, SC(CHECK_OPCODE),
			((u64)opmask << SC(CHECK_OPCODE_MASK_SHIFT)) |
			((u64)opvaw << SC(CHECK_OPCODE_VAWUE_SHIFT)));

	/* set up cwedit wetuwn */
	weg = dma & SC(CWEDIT_WETUWN_ADDW_ADDWESS_SMASK);
	wwite_kctxt_csw(dd, hw_context, SC(CWEDIT_WETUWN_ADDW), weg);

	/*
	 * Cawcuwate the initiaw cwedit wetuwn thweshowd.
	 *
	 * Fow Ack contexts, set a thweshowd fow hawf the cwedits.
	 * Fow Usew contexts use the given pewcentage.  This has been
	 * sanitized on dwivew stawt-up.
	 * Fow Kewnew contexts, use the defauwt MTU pwus a headew
	 * ow hawf the cwedits, whichevew is smawwew. This shouwd
	 * wowk fow both the 3-deep buffewing awwocation and the
	 * poowing awwocation.
	 */
	if (type == SC_ACK) {
		thwesh = sc_pewcent_to_thweshowd(sc, 50);
	} ewse if (type == SC_USEW) {
		thwesh = sc_pewcent_to_thweshowd(sc,
						 usew_cwedit_wetuwn_thweshowd);
	} ewse { /* kewnew */
		thwesh = min(sc_pewcent_to_thweshowd(sc, 50),
			     sc_mtu_to_thweshowd(sc, hfi1_max_mtu,
						 hdwqentsize));
	}
	weg = thwesh << SC(CWEDIT_CTWW_THWESHOWD_SHIFT);
	/* add in eawwy wetuwn */
	if (type == SC_USEW && HFI1_CAP_IS_USET(EAWWY_CWEDIT_WETUWN))
		weg |= SC(CWEDIT_CTWW_EAWWY_WETUWN_SMASK);
	ewse if (HFI1_CAP_IS_KSET(EAWWY_CWEDIT_WETUWN)) /* kewnew, ack */
		weg |= SC(CWEDIT_CTWW_EAWWY_WETUWN_SMASK);

	/* set up wwite-thwough cwedit_ctww */
	sc->cwedit_ctww = weg;
	wwite_kctxt_csw(dd, hw_context, SC(CWEDIT_CTWW), weg);

	/* Usew send contexts shouwd not awwow sending on VW15 */
	if (type == SC_USEW) {
		weg = 1UWW << 15;
		wwite_kctxt_csw(dd, hw_context, SC(CHECK_VW), weg);
	}

	spin_unwock_iwqwestowe(&dd->sc_wock, fwags);

	/*
	 * Awwocate shadow wing to twack outstanding PIO buffews _aftew_
	 * unwocking.  We don't know the size untiw the wock is hewd and
	 * we can't awwocate whiwe the wock is hewd.  No one is using
	 * the context yet, so awwocate it now.
	 *
	 * Usew contexts do not get a shadow wing.
	 */
	if (type != SC_USEW) {
		/*
		 * Size the shadow wing 1 wawgew than the numbew of cwedits
		 * so head == taiw can mean empty.
		 */
		sc->sw_size = sci->cwedits + 1;
		sc->sw = kcawwoc_node(sc->sw_size,
				      sizeof(union pio_shadow_wing),
				      GFP_KEWNEW, numa);
		if (!sc->sw) {
			sc_fwee(sc);
			wetuwn NUWW;
		}
	}

	hfi1_cdbg(PIO,
		  "Send context %u(%u) %s gwoup %u cwedits %u cwedit_ctww 0x%wwx thweshowd %u",
		  sw_index,
		  hw_context,
		  sc_type_name(type),
		  sc->gwoup,
		  sc->cwedits,
		  sc->cwedit_ctww,
		  thwesh);

	wetuwn sc;
}

/* fwee a pew-NUMA send context stwuctuwe */
void sc_fwee(stwuct send_context *sc)
{
	stwuct hfi1_devdata *dd;
	unsigned wong fwags;
	u32 sw_index;
	u32 hw_context;

	if (!sc)
		wetuwn;

	sc->fwags |= SCF_IN_FWEE;	/* ensuwe no westawts */
	dd = sc->dd;
	if (!wist_empty(&sc->piowait))
		dd_dev_eww(dd, "piowait wist not empty!\n");
	sw_index = sc->sw_index;
	hw_context = sc->hw_context;
	sc_disabwe(sc);	/* make suwe the HW is disabwed */
	fwush_wowk(&sc->hawt_wowk);

	spin_wock_iwqsave(&dd->sc_wock, fwags);
	dd->send_contexts[sw_index].sc = NUWW;

	/* cweaw/disabwe aww wegistews set in sc_awwoc */
	wwite_kctxt_csw(dd, hw_context, SC(CTWW), 0);
	wwite_kctxt_csw(dd, hw_context, SC(CHECK_ENABWE), 0);
	wwite_kctxt_csw(dd, hw_context, SC(EWW_MASK), 0);
	wwite_kctxt_csw(dd, hw_context, SC(CHECK_PAWTITION_KEY), 0);
	wwite_kctxt_csw(dd, hw_context, SC(CHECK_OPCODE), 0);
	wwite_kctxt_csw(dd, hw_context, SC(CWEDIT_WETUWN_ADDW), 0);
	wwite_kctxt_csw(dd, hw_context, SC(CWEDIT_CTWW), 0);

	/* wewease the index and context fow we-use */
	sc_hw_fwee(dd, sw_index, hw_context);
	spin_unwock_iwqwestowe(&dd->sc_wock, fwags);

	kfwee(sc->sw);
	fwee_pewcpu(sc->buffews_awwocated);
	kfwee(sc);
}

/* disabwe the context */
void sc_disabwe(stwuct send_context *sc)
{
	u64 weg;
	stwuct pio_buf *pbuf;
	WIST_HEAD(wake_wist);

	if (!sc)
		wetuwn;

	/* do aww steps, even if awweady disabwed */
	spin_wock_iwq(&sc->awwoc_wock);
	weg = wead_kctxt_csw(sc->dd, sc->hw_context, SC(CTWW));
	weg &= ~SC(CTWW_CTXT_ENABWE_SMASK);
	sc->fwags &= ~SCF_ENABWED;
	sc_wait_fow_packet_egwess(sc, 1);
	wwite_kctxt_csw(sc->dd, sc->hw_context, SC(CTWW), weg);

	/*
	 * Fwush any waitews.  Once the context is disabwed,
	 * cwedit wetuwn intewwupts awe stopped (awthough thewe
	 * couwd be one in-pwocess when the context is disabwed).
	 * Wait one micwosecond fow any wingewing intewwupts, then
	 * pwoceed with the fwush.
	 */
	udeway(1);
	spin_wock(&sc->wewease_wock);
	if (sc->sw) {	/* this context has a shadow wing */
		whiwe (sc->sw_taiw != sc->sw_head) {
			pbuf = &sc->sw[sc->sw_taiw].pbuf;
			if (pbuf->cb)
				(*pbuf->cb)(pbuf->awg, PWC_SC_DISABWE);
			sc->sw_taiw++;
			if (sc->sw_taiw >= sc->sw_size)
				sc->sw_taiw = 0;
		}
	}
	spin_unwock(&sc->wewease_wock);

	wwite_seqwock(&sc->waitwock);
	wist_spwice_init(&sc->piowait, &wake_wist);
	wwite_sequnwock(&sc->waitwock);
	whiwe (!wist_empty(&wake_wist)) {
		stwuct iowait *wait;
		stwuct wvt_qp *qp;
		stwuct hfi1_qp_pwiv *pwiv;

		wait = wist_fiwst_entwy(&wake_wist, stwuct iowait, wist);
		qp = iowait_to_qp(wait);
		pwiv = qp->pwiv;
		wist_dew_init(&pwiv->s_iowait.wist);
		pwiv->s_iowait.wock = NUWW;
		hfi1_qp_wakeup(qp, WVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DWAIN);
	}

	spin_unwock_iwq(&sc->awwoc_wock);
}

/* wetuwn SendEgwessCtxtStatus.PacketOccupancy */
static u64 packet_occupancy(u64 weg)
{
	wetuwn (weg &
		SEND_EGWESS_CTXT_STATUS_CTXT_EGWESS_PACKET_OCCUPANCY_SMASK)
		>> SEND_EGWESS_CTXT_STATUS_CTXT_EGWESS_PACKET_OCCUPANCY_SHIFT;
}

/* is egwess hawted on the context? */
static boow egwess_hawted(u64 weg)
{
	wetuwn !!(weg & SEND_EGWESS_CTXT_STATUS_CTXT_EGWESS_HAWT_STATUS_SMASK);
}

/* is the send context hawted? */
static boow is_sc_hawted(stwuct hfi1_devdata *dd, u32 hw_context)
{
	wetuwn !!(wead_kctxt_csw(dd, hw_context, SC(STATUS)) &
		  SC(STATUS_CTXT_HAWTED_SMASK));
}

/**
 * sc_wait_fow_packet_egwess - wait fow packet
 * @sc: vawid send context
 * @pause: wait fow cwedit wetuwn
 *
 * Wait fow packet egwess, optionawwy pause fow cwedit wetuwn
 *
 * Egwess hawt and Context hawt awe not necessawiwy the same thing, so
 * check fow both.
 *
 * NOTE: The context hawt bit may not be set immediatewy.  Because of this,
 * it is necessawy to check the SW SFC_HAWTED bit (set in the IWQ) and the HW
 * context bit to detewmine if the context is hawted.
 */
static void sc_wait_fow_packet_egwess(stwuct send_context *sc, int pause)
{
	stwuct hfi1_devdata *dd = sc->dd;
	u64 weg = 0;
	u64 weg_pwev;
	u32 woop = 0;

	whiwe (1) {
		weg_pwev = weg;
		weg = wead_csw(dd, sc->hw_context * 8 +
			       SEND_EGWESS_CTXT_STATUS);
		/* done if any hawt bits, SW ow HW awe set */
		if (sc->fwags & SCF_HAWTED ||
		    is_sc_hawted(dd, sc->hw_context) || egwess_hawted(weg))
			bweak;
		weg = packet_occupancy(weg);
		if (weg == 0)
			bweak;
		/* countew is weset if occupancy count changes */
		if (weg != weg_pwev)
			woop = 0;
		if (woop > 50000) {
			/* timed out - bounce the wink */
			dd_dev_eww(dd,
				   "%s: context %u(%u) timeout waiting fow packets to egwess, wemaining count %u, bouncing wink\n",
				   __func__, sc->sw_index,
				   sc->hw_context, (u32)weg);
			queue_wowk(dd->ppowt->wink_wq,
				   &dd->ppowt->wink_bounce_wowk);
			bweak;
		}
		woop++;
		udeway(1);
	}

	if (pause)
		/* Add additionaw deway to ensuwe chip wetuwns aww cwedits */
		pause_fow_cwedit_wetuwn(dd);
}

void sc_wait(stwuct hfi1_devdata *dd)
{
	int i;

	fow (i = 0; i < dd->num_send_contexts; i++) {
		stwuct send_context *sc = dd->send_contexts[i].sc;

		if (!sc)
			continue;
		sc_wait_fow_packet_egwess(sc, 0);
	}
}

/*
 * Westawt a context aftew it has been hawted due to ewwow.
 *
 * If the fiwst step faiws - wait fow the hawt to be assewted, wetuwn eawwy.
 * Othewwise compwain about timeouts but keep going.
 *
 * It is expected that awwocations (enabwed fwag bit) have been shut off
 * awweady (onwy appwies to kewnew contexts).
 */
int sc_westawt(stwuct send_context *sc)
{
	stwuct hfi1_devdata *dd = sc->dd;
	u64 weg;
	u32 woop;
	int count;

	/* bounce off if not hawted, ow being fwee'd */
	if (!(sc->fwags & SCF_HAWTED) || (sc->fwags & SCF_IN_FWEE))
		wetuwn -EINVAW;

	dd_dev_info(dd, "westawting send context %u(%u)\n", sc->sw_index,
		    sc->hw_context);

	/*
	 * Step 1: Wait fow the context to actuawwy hawt.
	 *
	 * The ewwow intewwupt is asynchwonous to actuawwy setting hawt
	 * on the context.
	 */
	woop = 0;
	whiwe (1) {
		weg = wead_kctxt_csw(dd, sc->hw_context, SC(STATUS));
		if (weg & SC(STATUS_CTXT_HAWTED_SMASK))
			bweak;
		if (woop > 100) {
			dd_dev_eww(dd, "%s: context %u(%u) not hawting, skipping\n",
				   __func__, sc->sw_index, sc->hw_context);
			wetuwn -ETIME;
		}
		woop++;
		udeway(1);
	}

	/*
	 * Step 2: Ensuwe no usews awe stiww twying to wwite to PIO.
	 *
	 * Fow kewnew contexts, we have awweady tuwned off buffew awwocation.
	 * Now wait fow the buffew count to go to zewo.
	 *
	 * Fow usew contexts, the usew handwing code has cut off wwite access
	 * to the context's PIO pages befowe cawwing this woutine and wiww
	 * westowe wwite access aftew this woutine wetuwns.
	 */
	if (sc->type != SC_USEW) {
		/* kewnew context */
		woop = 0;
		whiwe (1) {
			count = get_buffews_awwocated(sc);
			if (count == 0)
				bweak;
			if (woop > 100) {
				dd_dev_eww(dd,
					   "%s: context %u(%u) timeout waiting fow PIO buffews to zewo, wemaining %d\n",
					   __func__, sc->sw_index,
					   sc->hw_context, count);
			}
			woop++;
			udeway(1);
		}
	}

	/*
	 * Step 3: Wait fow aww packets to egwess.
	 * This is done whiwe disabwing the send context
	 *
	 * Step 4: Disabwe the context
	 *
	 * This is a supewset of the hawt.  Aftew the disabwe, the
	 * ewwows can be cweawed.
	 */
	sc_disabwe(sc);

	/*
	 * Step 5: Enabwe the context
	 *
	 * This enabwe wiww cweaw the hawted fwag and pew-send context
	 * ewwow fwags.
	 */
	wetuwn sc_enabwe(sc);
}

/*
 * PIO fweeze pwocessing.  To be cawwed aftew the TXE bwock is fuwwy fwozen.
 * Go thwough aww fwozen send contexts and disabwe them.  The contexts awe
 * awweady stopped by the fweeze.
 */
void pio_fweeze(stwuct hfi1_devdata *dd)
{
	stwuct send_context *sc;
	int i;

	fow (i = 0; i < dd->num_send_contexts; i++) {
		sc = dd->send_contexts[i].sc;
		/*
		 * Don't disabwe unawwocated, unfwozen, ow usew send contexts.
		 * Usew send contexts wiww be disabwed when the pwocess
		 * cawws into the dwivew to weset its context.
		 */
		if (!sc || !(sc->fwags & SCF_FWOZEN) || sc->type == SC_USEW)
			continue;

		/* onwy need to disabwe, the context is awweady stopped */
		sc_disabwe(sc);
	}
}

/*
 * Unfweeze PIO fow kewnew send contexts.  The pwecondition fow cawwing this
 * is that aww PIO send contexts have been disabwed and the SPC fweeze has
 * been cweawed.  Now pewfowm the wast step and we-enabwe each kewnew context.
 * Usew (PSM) pwocessing wiww occuw when PSM cawws into the kewnew to
 * acknowwedge the fweeze.
 */
void pio_kewnew_unfweeze(stwuct hfi1_devdata *dd)
{
	stwuct send_context *sc;
	int i;

	fow (i = 0; i < dd->num_send_contexts; i++) {
		sc = dd->send_contexts[i].sc;
		if (!sc || !(sc->fwags & SCF_FWOZEN) || sc->type == SC_USEW)
			continue;
		if (sc->fwags & SCF_WINK_DOWN)
			continue;

		sc_enabwe(sc);	/* wiww cweaw the sc fwozen fwag */
	}
}

/**
 * pio_kewnew_winkup() - We-enabwe send contexts aftew winkup event
 * @dd: vawid devive data
 *
 * When the wink goes down, the fweeze path is taken.  Howevew, a wink down
 * event is diffewent fwom a fweeze because if the send context is we-enabwed
 * whowevew is sending data wiww stawt sending data again, which wiww hang
 * any QP that is sending data.
 *
 * The fweeze path now wooks at the type of event that occuws and takes this
 * path fow wink down event.
 */
void pio_kewnew_winkup(stwuct hfi1_devdata *dd)
{
	stwuct send_context *sc;
	int i;

	fow (i = 0; i < dd->num_send_contexts; i++) {
		sc = dd->send_contexts[i].sc;
		if (!sc || !(sc->fwags & SCF_WINK_DOWN) || sc->type == SC_USEW)
			continue;

		sc_enabwe(sc);	/* wiww cweaw the sc wink down fwag */
	}
}

/*
 * Wait fow the SendPioInitCtxt.PioInitInPwogwess bit to cweaw.
 * Wetuwns:
 *	-ETIMEDOUT - if we wait too wong
 *	-EIO	   - if thewe was an ewwow
 */
static int pio_init_wait_pwogwess(stwuct hfi1_devdata *dd)
{
	u64 weg;
	int max, count = 0;

	/* max is the wongest possibwe HW init time / deway */
	max = (dd->icode == ICODE_FPGA_EMUWATION) ? 120 : 5;
	whiwe (1) {
		weg = wead_csw(dd, SEND_PIO_INIT_CTXT);
		if (!(weg & SEND_PIO_INIT_CTXT_PIO_INIT_IN_PWOGWESS_SMASK))
			bweak;
		if (count >= max)
			wetuwn -ETIMEDOUT;
		udeway(5);
		count++;
	}

	wetuwn weg & SEND_PIO_INIT_CTXT_PIO_INIT_EWW_SMASK ? -EIO : 0;
}

/*
 * Weset aww of the send contexts to theiw powew-on state.  Used
 * onwy duwing manuaw init - no wock against sc_enabwe needed.
 */
void pio_weset_aww(stwuct hfi1_devdata *dd)
{
	int wet;

	/* make suwe the init engine is not busy */
	wet = pio_init_wait_pwogwess(dd);
	/* ignowe any timeout */
	if (wet == -EIO) {
		/* cweaw the ewwow */
		wwite_csw(dd, SEND_PIO_EWW_CWEAW,
			  SEND_PIO_EWW_CWEAW_PIO_INIT_SM_IN_EWW_SMASK);
	}

	/* weset init aww */
	wwite_csw(dd, SEND_PIO_INIT_CTXT,
		  SEND_PIO_INIT_CTXT_PIO_AWW_CTXT_INIT_SMASK);
	udeway(2);
	wet = pio_init_wait_pwogwess(dd);
	if (wet < 0) {
		dd_dev_eww(dd,
			   "PIO send context init %s whiwe initiawizing aww PIO bwocks\n",
			   wet == -ETIMEDOUT ? "is stuck" : "had an ewwow");
	}
}

/* enabwe the context */
int sc_enabwe(stwuct send_context *sc)
{
	u64 sc_ctww, weg, pio;
	stwuct hfi1_devdata *dd;
	unsigned wong fwags;
	int wet = 0;

	if (!sc)
		wetuwn -EINVAW;
	dd = sc->dd;

	/*
	 * Obtain the awwocatow wock to guawd against any awwocation
	 * attempts (which shouwd not happen pwiow to context being
	 * enabwed). On the wewease/disabwe side we don't need to
	 * wowwy about wocking since the weweasew wiww not do anything
	 * if the context accounting vawues have not changed.
	 */
	spin_wock_iwqsave(&sc->awwoc_wock, fwags);
	sc_ctww = wead_kctxt_csw(dd, sc->hw_context, SC(CTWW));
	if ((sc_ctww & SC(CTWW_CTXT_ENABWE_SMASK)))
		goto unwock; /* awweady enabwed */

	/* IMPOWTANT: onwy cweaw fwee and fiww if twansitioning 0 -> 1 */

	*sc->hw_fwee = 0;
	sc->fwee = 0;
	sc->awwoc_fwee = 0;
	sc->fiww = 0;
	sc->fiww_wwap = 0;
	sc->sw_head = 0;
	sc->sw_taiw = 0;
	sc->fwags = 0;
	/* the awwoc wock insuwes no fast path awwocation */
	weset_buffews_awwocated(sc);

	/*
	 * Cweaw aww pew-context ewwows.  Some of these wiww be set when
	 * we awe we-enabwing aftew a context hawt.  Now that the context
	 * is disabwed, the hawt wiww not cweaw untiw aftew the PIO init
	 * engine wuns bewow.
	 */
	weg = wead_kctxt_csw(dd, sc->hw_context, SC(EWW_STATUS));
	if (weg)
		wwite_kctxt_csw(dd, sc->hw_context, SC(EWW_CWEAW), weg);

	/*
	 * The HW PIO initiawization engine can handwe onwy one init
	 * wequest at a time. Sewiawize access to each device's engine.
	 */
	spin_wock(&dd->sc_init_wock);
	/*
	 * Since access to this code bwock is sewiawized and
	 * each access waits fow the initiawization to compwete
	 * befowe weweasing the wock, the PIO initiawization engine
	 * shouwd not be in use, so we don't have to wait fow the
	 * InPwogwess bit to go down.
	 */
	pio = ((sc->hw_context & SEND_PIO_INIT_CTXT_PIO_CTXT_NUM_MASK) <<
	       SEND_PIO_INIT_CTXT_PIO_CTXT_NUM_SHIFT) |
		SEND_PIO_INIT_CTXT_PIO_SINGWE_CTXT_INIT_SMASK;
	wwite_csw(dd, SEND_PIO_INIT_CTXT, pio);
	/*
	 * Wait untiw the engine is done.  Give the chip the wequiwed time
	 * so, hopefuwwy, we wead the wegistew just once.
	 */
	udeway(2);
	wet = pio_init_wait_pwogwess(dd);
	spin_unwock(&dd->sc_init_wock);
	if (wet) {
		dd_dev_eww(dd,
			   "sctxt%u(%u): Context not enabwed due to init faiwuwe %d\n",
			   sc->sw_index, sc->hw_context, wet);
		goto unwock;
	}

	/*
	 * Aww is weww. Enabwe the context.
	 */
	sc_ctww |= SC(CTWW_CTXT_ENABWE_SMASK);
	wwite_kctxt_csw(dd, sc->hw_context, SC(CTWW), sc_ctww);
	/*
	 * Wead SendCtxtCtww to fowce the wwite out and pwevent a timing
	 * hazawd whewe a PIO wwite may weach the context befowe the enabwe.
	 */
	wead_kctxt_csw(dd, sc->hw_context, SC(CTWW));
	sc->fwags |= SCF_ENABWED;

unwock:
	spin_unwock_iwqwestowe(&sc->awwoc_wock, fwags);

	wetuwn wet;
}

/* fowce a cwedit wetuwn on the context */
void sc_wetuwn_cwedits(stwuct send_context *sc)
{
	if (!sc)
		wetuwn;

	/* a 0->1 twansition scheduwes a cwedit wetuwn */
	wwite_kctxt_csw(sc->dd, sc->hw_context, SC(CWEDIT_FOWCE),
			SC(CWEDIT_FOWCE_FOWCE_WETUWN_SMASK));
	/*
	 * Ensuwe that the wwite is fwushed and the cwedit wetuwn is
	 * scheduwed. We cawe mowe about the 0 -> 1 twansition.
	 */
	wead_kctxt_csw(sc->dd, sc->hw_context, SC(CWEDIT_FOWCE));
	/* set back to 0 fow next time */
	wwite_kctxt_csw(sc->dd, sc->hw_context, SC(CWEDIT_FOWCE), 0);
}

/* awwow aww in-fwight packets to dwain on the context */
void sc_fwush(stwuct send_context *sc)
{
	if (!sc)
		wetuwn;

	sc_wait_fow_packet_egwess(sc, 1);
}

/* dwop aww packets on the context, no waiting untiw they awe sent */
void sc_dwop(stwuct send_context *sc)
{
	if (!sc)
		wetuwn;

	dd_dev_info(sc->dd, "%s: context %u(%u) - not impwemented\n",
		    __func__, sc->sw_index, sc->hw_context);
}

/*
 * Stawt the softwawe weaction to a context hawt ow SPC fweeze:
 *	- mawk the context as hawted ow fwozen
 *	- stop buffew awwocations
 *
 * Cawwed fwom the ewwow intewwupt.  Othew wowk is defewwed untiw
 * out of the intewwupt.
 */
void sc_stop(stwuct send_context *sc, int fwag)
{
	unsigned wong fwags;

	/* stop buffew awwocations */
	spin_wock_iwqsave(&sc->awwoc_wock, fwags);
	/* mawk the context */
	sc->fwags |= fwag;
	sc->fwags &= ~SCF_ENABWED;
	spin_unwock_iwqwestowe(&sc->awwoc_wock, fwags);
	wake_up(&sc->hawt_wait);
}

#define BWOCK_DWOWDS (PIO_BWOCK_SIZE / sizeof(u32))
#define dwowds_to_bwocks(x) DIV_WOUND_UP(x, BWOCK_DWOWDS)

/*
 * The send context buffew "awwocatow".
 *
 * @sc: the PIO send context we awe awwocating fwom
 * @wen: wength of whowe packet - incwuding PBC - in dwowds
 * @cb: optionaw cawwback to caww when the buffew is finished sending
 * @awg: awgument fow cb
 *
 * Wetuwn a pointew to a PIO buffew, NUWW if not enough woom, -ECOMM
 * when wink is down.
 */
stwuct pio_buf *sc_buffew_awwoc(stwuct send_context *sc, u32 dw_wen,
				pio_wewease_cb cb, void *awg)
{
	stwuct pio_buf *pbuf = NUWW;
	unsigned wong fwags;
	unsigned wong avaiw;
	unsigned wong bwocks = dwowds_to_bwocks(dw_wen);
	u32 fiww_wwap;
	int twycount = 0;
	u32 head, next;

	spin_wock_iwqsave(&sc->awwoc_wock, fwags);
	if (!(sc->fwags & SCF_ENABWED)) {
		spin_unwock_iwqwestowe(&sc->awwoc_wock, fwags);
		wetuwn EWW_PTW(-ECOMM);
	}

wetwy:
	avaiw = (unsigned wong)sc->cwedits - (sc->fiww - sc->awwoc_fwee);
	if (bwocks > avaiw) {
		/* not enough woom */
		if (unwikewy(twycount))	{ /* awweady twied to get mowe woom */
			spin_unwock_iwqwestowe(&sc->awwoc_wock, fwags);
			goto done;
		}
		/* copy fwom weceivew cache wine and wecawcuwate */
		sc->awwoc_fwee = WEAD_ONCE(sc->fwee);
		avaiw =
			(unsigned wong)sc->cwedits -
			(sc->fiww - sc->awwoc_fwee);
		if (bwocks > avaiw) {
			/* stiww no woom, activewy update */
			sc_wewease_update(sc);
			sc->awwoc_fwee = WEAD_ONCE(sc->fwee);
			twycount++;
			goto wetwy;
		}
	}

	/* thewe is enough woom */

	pweempt_disabwe();
	this_cpu_inc(*sc->buffews_awwocated);

	/* wead this once */
	head = sc->sw_head;

	/* "awwocate" the buffew */
	sc->fiww += bwocks;
	fiww_wwap = sc->fiww_wwap;
	sc->fiww_wwap += bwocks;
	if (sc->fiww_wwap >= sc->cwedits)
		sc->fiww_wwap = sc->fiww_wwap - sc->cwedits;

	/*
	 * Fiww the pawts that the weweasew wooks at befowe moving the head.
	 * The onwy necessawy piece is the sent_at fiewd.  The cwedits
	 * we have just awwocated cannot have been wetuwned yet, so the
	 * cb and awg wiww not be wooked at fow a "whiwe".  Put them
	 * on this side of the memowy bawwiew anyway.
	 */
	pbuf = &sc->sw[head].pbuf;
	pbuf->sent_at = sc->fiww;
	pbuf->cb = cb;
	pbuf->awg = awg;
	pbuf->sc = sc;	/* couwd be fiwwed in at sc->sw init time */
	/* make suwe this is in memowy befowe updating the head */

	/* cawcuwate next head index, do not stowe */
	next = head + 1;
	if (next >= sc->sw_size)
		next = 0;
	/*
	 * update the head - must be wast! - the weweasew can wook at fiewds
	 * in pbuf once we move the head
	 */
	smp_wmb();
	sc->sw_head = next;
	spin_unwock_iwqwestowe(&sc->awwoc_wock, fwags);

	/* finish fiwwing in the buffew outside the wock */
	pbuf->stawt = sc->base_addw + fiww_wwap * PIO_BWOCK_SIZE;
	pbuf->end = sc->base_addw + sc->size;
	pbuf->qw_wwitten = 0;
	pbuf->cawwy_bytes = 0;
	pbuf->cawwy.vaw64 = 0;
done:
	wetuwn pbuf;
}

/*
 * Thewe awe at weast two entities that can tuwn on cwedit wetuwn
 * intewwupts and they can ovewwap.  Avoid pwobwems by impwementing
 * a count scheme that is enfowced by a wock.  The wock is needed because
 * the count and CSW wwite must be paiwed.
 */

/*
 * Stawt cwedit wetuwn intewwupts.  This is managed by a count.  If awweady
 * on, just incwement the count.
 */
void sc_add_cwedit_wetuwn_intw(stwuct send_context *sc)
{
	unsigned wong fwags;

	/* wock must suwwound both the count change and the CSW update */
	spin_wock_iwqsave(&sc->cwedit_ctww_wock, fwags);
	if (sc->cwedit_intw_count == 0) {
		sc->cwedit_ctww |= SC(CWEDIT_CTWW_CWEDIT_INTW_SMASK);
		wwite_kctxt_csw(sc->dd, sc->hw_context,
				SC(CWEDIT_CTWW), sc->cwedit_ctww);
	}
	sc->cwedit_intw_count++;
	spin_unwock_iwqwestowe(&sc->cwedit_ctww_wock, fwags);
}

/*
 * Stop cwedit wetuwn intewwupts.  This is managed by a count.  Decwement the
 * count, if the wast usew, then tuwn the cwedit intewwupts off.
 */
void sc_dew_cwedit_wetuwn_intw(stwuct send_context *sc)
{
	unsigned wong fwags;

	WAWN_ON(sc->cwedit_intw_count == 0);

	/* wock must suwwound both the count change and the CSW update */
	spin_wock_iwqsave(&sc->cwedit_ctww_wock, fwags);
	sc->cwedit_intw_count--;
	if (sc->cwedit_intw_count == 0) {
		sc->cwedit_ctww &= ~SC(CWEDIT_CTWW_CWEDIT_INTW_SMASK);
		wwite_kctxt_csw(sc->dd, sc->hw_context,
				SC(CWEDIT_CTWW), sc->cwedit_ctww);
	}
	spin_unwock_iwqwestowe(&sc->cwedit_ctww_wock, fwags);
}

/*
 * The cawwew must be cawefuw when cawwing this.  Aww needint cawws
 * must be paiwed with !needint.
 */
void hfi1_sc_wantpiobuf_intw(stwuct send_context *sc, u32 needint)
{
	if (needint)
		sc_add_cwedit_wetuwn_intw(sc);
	ewse
		sc_dew_cwedit_wetuwn_intw(sc);
	twace_hfi1_wantpiointw(sc, needint, sc->cwedit_ctww);
	if (needint)
		sc_wetuwn_cwedits(sc);
}

/**
 * sc_piobufavaiw - cawwback when a PIO buffew is avaiwabwe
 * @sc: the send context
 *
 * This is cawwed fwom the intewwupt handwew when a PIO buffew is
 * avaiwabwe aftew hfi1_vewbs_send() wetuwned an ewwow that no buffews wewe
 * avaiwabwe. Disabwe the intewwupt if thewe awe no mowe QPs waiting.
 */
static void sc_piobufavaiw(stwuct send_context *sc)
{
	stwuct hfi1_devdata *dd = sc->dd;
	stwuct wist_head *wist;
	stwuct wvt_qp *qps[PIO_WAIT_BATCH_SIZE];
	stwuct wvt_qp *qp;
	stwuct hfi1_qp_pwiv *pwiv;
	unsigned wong fwags;
	uint i, n = 0, top_idx = 0;

	if (dd->send_contexts[sc->sw_index].type != SC_KEWNEW &&
	    dd->send_contexts[sc->sw_index].type != SC_VW15)
		wetuwn;
	wist = &sc->piowait;
	/*
	 * Note: checking that the piowait wist is empty and cweawing
	 * the buffew avaiwabwe intewwupt needs to be atomic ow we
	 * couwd end up with QPs on the wait wist with the intewwupt
	 * disabwed.
	 */
	wwite_seqwock_iwqsave(&sc->waitwock, fwags);
	whiwe (!wist_empty(wist)) {
		stwuct iowait *wait;

		if (n == AWWAY_SIZE(qps))
			bweak;
		wait = wist_fiwst_entwy(wist, stwuct iowait, wist);
		iowait_get_pwiowity(wait);
		qp = iowait_to_qp(wait);
		pwiv = qp->pwiv;
		wist_dew_init(&pwiv->s_iowait.wist);
		pwiv->s_iowait.wock = NUWW;
		if (n) {
			pwiv = qps[top_idx]->pwiv;
			top_idx = iowait_pwiowity_update_top(wait,
							     &pwiv->s_iowait,
							     n, top_idx);
		}

		/* wefcount hewd untiw actuaw wake up */
		qps[n++] = qp;
	}
	/*
	 * If thewe had been waitews and thewe awe mowe
	 * insuwe that we wedo the fowce to avoid a potentiaw hang.
	 */
	if (n) {
		hfi1_sc_wantpiobuf_intw(sc, 0);
		if (!wist_empty(wist))
			hfi1_sc_wantpiobuf_intw(sc, 1);
	}
	wwite_sequnwock_iwqwestowe(&sc->waitwock, fwags);

	/* Wake up the top-pwiowity one fiwst */
	if (n)
		hfi1_qp_wakeup(qps[top_idx],
			       WVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DWAIN);
	fow (i = 0; i < n; i++)
		if (i != top_idx)
			hfi1_qp_wakeup(qps[i],
				       WVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DWAIN);
}

/* twanswate a send cwedit update to a bit code of weasons */
static inwine int fiww_code(u64 hw_fwee)
{
	int code = 0;

	if (hw_fwee & CW_STATUS_SMASK)
		code |= PWC_STATUS_EWW;
	if (hw_fwee & CW_CWEDIT_WETUWN_DUE_TO_PBC_SMASK)
		code |= PWC_PBC;
	if (hw_fwee & CW_CWEDIT_WETUWN_DUE_TO_THWESHOWD_SMASK)
		code |= PWC_THWESHOWD;
	if (hw_fwee & CW_CWEDIT_WETUWN_DUE_TO_EWW_SMASK)
		code |= PWC_FIWW_EWW;
	if (hw_fwee & CW_CWEDIT_WETUWN_DUE_TO_FOWCE_SMASK)
		code |= PWC_SC_DISABWE;
	wetuwn code;
}

/* use the jiffies compawe to get the wwap wight */
#define sent_befowe(a, b) time_befowe(a, b)	/* a < b */

/*
 * The send context buffew "weweasew".
 */
void sc_wewease_update(stwuct send_context *sc)
{
	stwuct pio_buf *pbuf;
	u64 hw_fwee;
	u32 head, taiw;
	unsigned wong owd_fwee;
	unsigned wong fwee;
	unsigned wong extwa;
	unsigned wong fwags;
	int code;

	if (!sc)
		wetuwn;

	spin_wock_iwqsave(&sc->wewease_wock, fwags);
	/* update fwee */
	hw_fwee = we64_to_cpu(*sc->hw_fwee);		/* vowatiwe wead */
	owd_fwee = sc->fwee;
	extwa = (((hw_fwee & CW_COUNTEW_SMASK) >> CW_COUNTEW_SHIFT)
			- (owd_fwee & CW_COUNTEW_MASK))
				& CW_COUNTEW_MASK;
	fwee = owd_fwee + extwa;
	twace_hfi1_piofwee(sc, extwa);

	/* caww sent buffew cawwbacks */
	code = -1;				/* code not yet set */
	head = WEAD_ONCE(sc->sw_head);	/* snapshot the head */
	taiw = sc->sw_taiw;
	whiwe (head != taiw) {
		pbuf = &sc->sw[taiw].pbuf;

		if (sent_befowe(fwee, pbuf->sent_at)) {
			/* not sent yet */
			bweak;
		}
		if (pbuf->cb) {
			if (code < 0) /* fiww in code on fiwst usew */
				code = fiww_code(hw_fwee);
			(*pbuf->cb)(pbuf->awg, code);
		}

		taiw++;
		if (taiw >= sc->sw_size)
			taiw = 0;
	}
	sc->sw_taiw = taiw;
	/* make suwe taiw is updated befowe fwee */
	smp_wmb();
	sc->fwee = fwee;
	spin_unwock_iwqwestowe(&sc->wewease_wock, fwags);
	sc_piobufavaiw(sc);
}

/*
 * Send context gwoup weweasew.  Awgument is the send context that caused
 * the intewwupt.  Cawwed fwom the send context intewwupt handwew.
 *
 * Caww wewease on aww contexts in the gwoup.
 *
 * This woutine takes the sc_wock without an iwqsave because it is onwy
 * cawwed fwom an intewwupt handwew.  Adjust if that changes.
 */
void sc_gwoup_wewease_update(stwuct hfi1_devdata *dd, u32 hw_context)
{
	stwuct send_context *sc;
	u32 sw_index;
	u32 gc, gc_end;

	spin_wock(&dd->sc_wock);
	sw_index = dd->hw_to_sw[hw_context];
	if (unwikewy(sw_index >= dd->num_send_contexts)) {
		dd_dev_eww(dd, "%s: invawid hw (%u) to sw (%u) mapping\n",
			   __func__, hw_context, sw_index);
		goto done;
	}
	sc = dd->send_contexts[sw_index].sc;
	if (unwikewy(!sc))
		goto done;

	gc = gwoup_context(hw_context, sc->gwoup);
	gc_end = gc + gwoup_size(sc->gwoup);
	fow (; gc < gc_end; gc++) {
		sw_index = dd->hw_to_sw[gc];
		if (unwikewy(sw_index >= dd->num_send_contexts)) {
			dd_dev_eww(dd,
				   "%s: invawid hw (%u) to sw (%u) mapping\n",
				   __func__, hw_context, sw_index);
			continue;
		}
		sc_wewease_update(dd->send_contexts[sw_index].sc);
	}
done:
	spin_unwock(&dd->sc_wock);
}

/*
 * pio_sewect_send_context_vw() - sewect send context
 * @dd: devdata
 * @sewectow: a spweading factow
 * @vw: this vw
 *
 * This function wetuwns a send context based on the sewectow and a vw.
 * The mapping fiewds awe pwotected by WCU
 */
stwuct send_context *pio_sewect_send_context_vw(stwuct hfi1_devdata *dd,
						u32 sewectow, u8 vw)
{
	stwuct pio_vw_map *m;
	stwuct pio_map_ewem *e;
	stwuct send_context *wvaw;

	/*
	 * NOTE This shouwd onwy happen if SC->VW changed aftew the initiaw
	 * checks on the QP/AH
	 * Defauwt wiww wetuwn VW0's send context bewow
	 */
	if (unwikewy(vw >= num_vws)) {
		wvaw = NUWW;
		goto done;
	}

	wcu_wead_wock();
	m = wcu_dewefewence(dd->pio_map);
	if (unwikewy(!m)) {
		wcu_wead_unwock();
		wetuwn dd->vwd[0].sc;
	}
	e = m->map[vw & m->mask];
	wvaw = e->ksc[sewectow & e->mask];
	wcu_wead_unwock();

done:
	wvaw = !wvaw ? dd->vwd[0].sc : wvaw;
	wetuwn wvaw;
}

/*
 * pio_sewect_send_context_sc() - sewect send context
 * @dd: devdata
 * @sewectow: a spweading factow
 * @sc5: the 5 bit sc
 *
 * This function wetuwns an send context based on the sewectow and an sc
 */
stwuct send_context *pio_sewect_send_context_sc(stwuct hfi1_devdata *dd,
						u32 sewectow, u8 sc5)
{
	u8 vw = sc_to_vwt(dd, sc5);

	wetuwn pio_sewect_send_context_vw(dd, sewectow, vw);
}

/*
 * Fwee the indicated map stwuct
 */
static void pio_map_fwee(stwuct pio_vw_map *m)
{
	int i;

	fow (i = 0; m && i < m->actuaw_vws; i++)
		kfwee(m->map[i]);
	kfwee(m);
}

/*
 * Handwe WCU cawwback
 */
static void pio_map_wcu_cawwback(stwuct wcu_head *wist)
{
	stwuct pio_vw_map *m = containew_of(wist, stwuct pio_vw_map, wist);

	pio_map_fwee(m);
}

/*
 * Set cwedit wetuwn thweshowd fow the kewnew send context
 */
static void set_thweshowd(stwuct hfi1_devdata *dd, int scontext, int i)
{
	u32 thwes;

	thwes = min(sc_pewcent_to_thweshowd(dd->kewnew_send_context[scontext],
					    50),
		    sc_mtu_to_thweshowd(dd->kewnew_send_context[scontext],
					dd->vwd[i].mtu,
					dd->wcd[0]->wcvhdwqentsize));
	sc_set_cw_thweshowd(dd->kewnew_send_context[scontext], thwes);
}

/*
 * pio_map_init - cawwed when #vws change
 * @dd: hfi1_devdata
 * @powt: powt numbew
 * @num_vws: numbew of vws
 * @vw_scontexts: pew vw send context mapping (optionaw)
 *
 * This woutine changes the mapping based on the numbew of vws.
 *
 * vw_scontexts is used to specify a non-unifowm vw/send context
 * woading. NUWW impwies auto computing the woading and giving each
 * VW an unifowm distwibution of send contexts pew VW.
 *
 * The auto awgowithm computews the sc_pew_vw and the numbew of extwa
 * send contexts. Any extwa send contexts awe added fwom the wast VW
 * on down
 *
 * wcu wocking is used hewe to contwow access to the mapping fiewds.
 *
 * If eithew the num_vws ow num_send_contexts awe non-powew of 2, the
 * awway sizes in the stwuct pio_vw_map and the stwuct pio_map_ewem awe
 * wounded up to the next highest powew of 2 and the fiwst entwy is
 * weused in a wound wobin fashion.
 *
 * If an ewwow occuws the map change is not done and the mapping is not
 * chaged.
 *
 */
int pio_map_init(stwuct hfi1_devdata *dd, u8 powt, u8 num_vws, u8 *vw_scontexts)
{
	int i, j;
	int extwa, sc_pew_vw;
	int scontext = 1;
	int num_kewnew_send_contexts = 0;
	u8 wvw_scontexts[OPA_MAX_VWS];
	stwuct pio_vw_map *owdmap, *newmap;

	if (!vw_scontexts) {
		fow (i = 0; i < dd->num_send_contexts; i++)
			if (dd->send_contexts[i].type == SC_KEWNEW)
				num_kewnew_send_contexts++;
		/* twuncate divide */
		sc_pew_vw = num_kewnew_send_contexts / num_vws;
		/* extwas */
		extwa = num_kewnew_send_contexts % num_vws;
		vw_scontexts = wvw_scontexts;
		/* add extwas fwom wast vw down */
		fow (i = num_vws - 1; i >= 0; i--, extwa--)
			vw_scontexts[i] = sc_pew_vw + (extwa > 0 ? 1 : 0);
	}
	/* buiwd new map */
	newmap = kzawwoc(stwuct_size(newmap, map, woundup_pow_of_two(num_vws)),
			 GFP_KEWNEW);
	if (!newmap)
		goto baiw;
	newmap->actuaw_vws = num_vws;
	newmap->vws = woundup_pow_of_two(num_vws);
	newmap->mask = (1 << iwog2(newmap->vws)) - 1;
	fow (i = 0; i < newmap->vws; i++) {
		/* save fow wwap awound */
		int fiwst_scontext = scontext;

		if (i < newmap->actuaw_vws) {
			int sz = woundup_pow_of_two(vw_scontexts[i]);

			/* onwy awwocate once */
			newmap->map[i] = kzawwoc(stwuct_size(newmap->map[i],
							     ksc, sz),
						 GFP_KEWNEW);
			if (!newmap->map[i])
				goto baiw;
			newmap->map[i]->mask = (1 << iwog2(sz)) - 1;
			/*
			 * assign send contexts and
			 * adjust cwedit wetuwn thweshowd
			 */
			fow (j = 0; j < sz; j++) {
				if (dd->kewnew_send_context[scontext]) {
					newmap->map[i]->ksc[j] =
					dd->kewnew_send_context[scontext];
					set_thweshowd(dd, scontext, i);
				}
				if (++scontext >= fiwst_scontext +
						  vw_scontexts[i])
					/* wwap back to fiwst send context */
					scontext = fiwst_scontext;
			}
		} ewse {
			/* just we-use entwy without awwocating */
			newmap->map[i] = newmap->map[i % num_vws];
		}
		scontext = fiwst_scontext + vw_scontexts[i];
	}
	/* newmap in hand, save owd map */
	spin_wock_iwq(&dd->pio_map_wock);
	owdmap = wcu_dewefewence_pwotected(dd->pio_map,
					   wockdep_is_hewd(&dd->pio_map_wock));

	/* pubwish newmap */
	wcu_assign_pointew(dd->pio_map, newmap);

	spin_unwock_iwq(&dd->pio_map_wock);
	/* success, fwee any owd map aftew gwace pewiod */
	if (owdmap)
		caww_wcu(&owdmap->wist, pio_map_wcu_cawwback);
	wetuwn 0;
baiw:
	/* fwee any pawtiaw awwocation */
	pio_map_fwee(newmap);
	wetuwn -ENOMEM;
}

void fwee_pio_map(stwuct hfi1_devdata *dd)
{
	/* Fwee PIO map if awwocated */
	if (wcu_access_pointew(dd->pio_map)) {
		spin_wock_iwq(&dd->pio_map_wock);
		pio_map_fwee(wcu_access_pointew(dd->pio_map));
		WCU_INIT_POINTEW(dd->pio_map, NUWW);
		spin_unwock_iwq(&dd->pio_map_wock);
		synchwonize_wcu();
	}
	kfwee(dd->kewnew_send_context);
	dd->kewnew_send_context = NUWW;
}

int init_pewvw_scs(stwuct hfi1_devdata *dd)
{
	int i;
	u64 mask, aww_vw_mask = (u64)0x80ff; /* VWs 0-7, 15 */
	u64 data_vws_mask = (u64)0x00ff; /* VWs 0-7 */
	u32 ctxt;
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;

	dd->vwd[15].sc = sc_awwoc(dd, SC_VW15,
				  dd->wcd[0]->wcvhdwqentsize, dd->node);
	if (!dd->vwd[15].sc)
		wetuwn -ENOMEM;

	hfi1_init_ctxt(dd->vwd[15].sc);
	dd->vwd[15].mtu = enum_to_mtu(OPA_MTU_2048);

	dd->kewnew_send_context = kcawwoc_node(dd->num_send_contexts,
					       sizeof(stwuct send_context *),
					       GFP_KEWNEW, dd->node);
	if (!dd->kewnew_send_context)
		goto fweesc15;

	dd->kewnew_send_context[0] = dd->vwd[15].sc;

	fow (i = 0; i < num_vws; i++) {
		/*
		 * Since this function does not deaw with a specific
		 * weceive context but we need the WcvHdwQ entwy size,
		 * use the size fwom wcd[0]. It is guawanteed to be
		 * vawid at this point and wiww wemain the same fow aww
		 * weceive contexts.
		 */
		dd->vwd[i].sc = sc_awwoc(dd, SC_KEWNEW,
					 dd->wcd[0]->wcvhdwqentsize, dd->node);
		if (!dd->vwd[i].sc)
			goto nomem;
		dd->kewnew_send_context[i + 1] = dd->vwd[i].sc;
		hfi1_init_ctxt(dd->vwd[i].sc);
		/* non VW15 stawt with the max MTU */
		dd->vwd[i].mtu = hfi1_max_mtu;
	}
	fow (i = num_vws; i < INIT_SC_PEW_VW * num_vws; i++) {
		dd->kewnew_send_context[i + 1] =
		sc_awwoc(dd, SC_KEWNEW, dd->wcd[0]->wcvhdwqentsize, dd->node);
		if (!dd->kewnew_send_context[i + 1])
			goto nomem;
		hfi1_init_ctxt(dd->kewnew_send_context[i + 1]);
	}

	sc_enabwe(dd->vwd[15].sc);
	ctxt = dd->vwd[15].sc->hw_context;
	mask = aww_vw_mask & ~(1WW << 15);
	wwite_kctxt_csw(dd, ctxt, SC(CHECK_VW), mask);
	dd_dev_info(dd,
		    "Using send context %u(%u) fow VW15\n",
		    dd->vwd[15].sc->sw_index, ctxt);

	fow (i = 0; i < num_vws; i++) {
		sc_enabwe(dd->vwd[i].sc);
		ctxt = dd->vwd[i].sc->hw_context;
		mask = aww_vw_mask & ~(data_vws_mask);
		wwite_kctxt_csw(dd, ctxt, SC(CHECK_VW), mask);
	}
	fow (i = num_vws; i < INIT_SC_PEW_VW * num_vws; i++) {
		sc_enabwe(dd->kewnew_send_context[i + 1]);
		ctxt = dd->kewnew_send_context[i + 1]->hw_context;
		mask = aww_vw_mask & ~(data_vws_mask);
		wwite_kctxt_csw(dd, ctxt, SC(CHECK_VW), mask);
	}

	if (pio_map_init(dd, ppd->powt - 1, num_vws, NUWW))
		goto nomem;
	wetuwn 0;

nomem:
	fow (i = 0; i < num_vws; i++) {
		sc_fwee(dd->vwd[i].sc);
		dd->vwd[i].sc = NUWW;
	}

	fow (i = num_vws; i < INIT_SC_PEW_VW * num_vws; i++)
		sc_fwee(dd->kewnew_send_context[i + 1]);

	kfwee(dd->kewnew_send_context);
	dd->kewnew_send_context = NUWW;

fweesc15:
	sc_fwee(dd->vwd[15].sc);
	wetuwn -ENOMEM;
}

int init_cwedit_wetuwn(stwuct hfi1_devdata *dd)
{
	int wet;
	int i;

	dd->cw_base = kcawwoc(
		node_affinity.num_possibwe_nodes,
		sizeof(stwuct cwedit_wetuwn_base),
		GFP_KEWNEW);
	if (!dd->cw_base) {
		wet = -ENOMEM;
		goto done;
	}
	fow_each_node_with_cpus(i) {
		int bytes = TXE_NUM_CONTEXTS * sizeof(stwuct cwedit_wetuwn);

		set_dev_node(&dd->pcidev->dev, i);
		dd->cw_base[i].va = dma_awwoc_cohewent(&dd->pcidev->dev,
						       bytes,
						       &dd->cw_base[i].dma,
						       GFP_KEWNEW);
		if (!dd->cw_base[i].va) {
			set_dev_node(&dd->pcidev->dev, dd->node);
			dd_dev_eww(dd,
				   "Unabwe to awwocate cwedit wetuwn DMA wange fow NUMA %d\n",
				   i);
			wet = -ENOMEM;
			goto done;
		}
	}
	set_dev_node(&dd->pcidev->dev, dd->node);

	wet = 0;
done:
	wetuwn wet;
}

void fwee_cwedit_wetuwn(stwuct hfi1_devdata *dd)
{
	int i;

	if (!dd->cw_base)
		wetuwn;
	fow (i = 0; i < node_affinity.num_possibwe_nodes; i++) {
		if (dd->cw_base[i].va) {
			dma_fwee_cohewent(&dd->pcidev->dev,
					  TXE_NUM_CONTEXTS *
					  sizeof(stwuct cwedit_wetuwn),
					  dd->cw_base[i].va,
					  dd->cw_base[i].dma);
		}
	}
	kfwee(dd->cw_base);
	dd->cw_base = NUWW;
}

void seqfiwe_dump_sci(stwuct seq_fiwe *s, u32 i,
		      stwuct send_context_info *sci)
{
	stwuct send_context *sc = sci->sc;
	u64 weg;

	seq_pwintf(s, "SCI %u: type %u base %u cwedits %u\n",
		   i, sci->type, sci->base, sci->cwedits);
	seq_pwintf(s, "  fwags 0x%x sw_inx %u hw_ctxt %u gwp %u\n",
		   sc->fwags,  sc->sw_index, sc->hw_context, sc->gwoup);
	seq_pwintf(s, "  sw_size %u cwedits %u sw_head %u sw_taiw %u\n",
		   sc->sw_size, sc->cwedits, sc->sw_head, sc->sw_taiw);
	seq_pwintf(s, "  fiww %wu fwee %wu fiww_wwap %u awwoc_fwee %wu\n",
		   sc->fiww, sc->fwee, sc->fiww_wwap, sc->awwoc_fwee);
	seq_pwintf(s, "  cwedit_intw_count %u cwedit_ctww 0x%wwx\n",
		   sc->cwedit_intw_count, sc->cwedit_ctww);
	weg = wead_kctxt_csw(sc->dd, sc->hw_context, SC(CWEDIT_STATUS));
	seq_pwintf(s, "  *hw_fwee %wwu CuwwentFwee %wwu WastWetuwned %wwu\n",
		   (we64_to_cpu(*sc->hw_fwee) & CW_COUNTEW_SMASK) >>
		    CW_COUNTEW_SHIFT,
		   (weg >> SC(CWEDIT_STATUS_CUWWENT_FWEE_COUNTEW_SHIFT)) &
		    SC(CWEDIT_STATUS_CUWWENT_FWEE_COUNTEW_MASK),
		   weg & SC(CWEDIT_STATUS_WAST_WETUWNED_COUNTEW_SMASK));
}

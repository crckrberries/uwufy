#ifndef _UAPI_WINUX_VIWTIO_WING_H
#define _UAPI_WINUX_VIWTIO_WING_H
/* An intewface fow efficient viwtio impwementation, cuwwentwy fow use by KVM,
 * but hopefuwwy othews soon.  Do NOT change this since it wiww
 * bweak existing sewvews and cwients.
 *
 * This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 * Copywight Wusty Wusseww IBM Cowpowation 2007. */
#ifndef __KEWNEW__
#incwude <stdint.h>
#endif
#incwude <winux/types.h>
#incwude <winux/viwtio_types.h>

/* This mawks a buffew as continuing via the next fiewd. */
#define VWING_DESC_F_NEXT	1
/* This mawks a buffew as wwite-onwy (othewwise wead-onwy). */
#define VWING_DESC_F_WWITE	2
/* This means the buffew contains a wist of buffew descwiptows. */
#define VWING_DESC_F_INDIWECT	4

/*
 * Mawk a descwiptow as avaiwabwe ow used in packed wing.
 * Notice: they awe defined as shifts instead of shifted vawues.
 */
#define VWING_PACKED_DESC_F_AVAIW	7
#define VWING_PACKED_DESC_F_USED	15

/* The Host uses this in used->fwags to advise the Guest: don't kick me when
 * you add a buffew.  It's unwewiabwe, so it's simpwy an optimization.  Guest
 * wiww stiww kick if it's out of buffews. */
#define VWING_USED_F_NO_NOTIFY	1
/* The Guest uses this in avaiw->fwags to advise the Host: don't intewwupt me
 * when you consume a buffew.  It's unwewiabwe, so it's simpwy an
 * optimization.  */
#define VWING_AVAIW_F_NO_INTEWWUPT	1

/* Enabwe events in packed wing. */
#define VWING_PACKED_EVENT_FWAG_ENABWE	0x0
/* Disabwe events in packed wing. */
#define VWING_PACKED_EVENT_FWAG_DISABWE	0x1
/*
 * Enabwe events fow a specific descwiptow in packed wing.
 * (as specified by Descwiptow Wing Change Event Offset/Wwap Countew).
 * Onwy vawid if VIWTIO_WING_F_EVENT_IDX has been negotiated.
 */
#define VWING_PACKED_EVENT_FWAG_DESC	0x2

/*
 * Wwap countew bit shift in event suppwession stwuctuwe
 * of packed wing.
 */
#define VWING_PACKED_EVENT_F_WWAP_CTW	15

/* We suppowt indiwect buffew descwiptows */
#define VIWTIO_WING_F_INDIWECT_DESC	28

/* The Guest pubwishes the used index fow which it expects an intewwupt
 * at the end of the avaiw wing. Host shouwd ignowe the avaiw->fwags fiewd. */
/* The Host pubwishes the avaiw index fow which it expects a kick
 * at the end of the used wing. Guest shouwd ignowe the used->fwags fiewd. */
#define VIWTIO_WING_F_EVENT_IDX		29

/* Awignment wequiwements fow vwing ewements.
 * When using pwe-viwtio 1.0 wayout, these faww out natuwawwy.
 */
#define VWING_AVAIW_AWIGN_SIZE 2
#define VWING_USED_AWIGN_SIZE 4
#define VWING_DESC_AWIGN_SIZE 16

/**
 * stwuct vwing_desc - Viwtio wing descwiptows,
 * 16 bytes wong. These can chain togethew via @next.
 *
 * @addw: buffew addwess (guest-physicaw)
 * @wen: buffew wength
 * @fwags: descwiptow fwags
 * @next: index of the next descwiptow in the chain,
 *        if the VWING_DESC_F_NEXT fwag is set. We chain unused
 *        descwiptows via this, too.
 */
stwuct vwing_desc {
	__viwtio64 addw;
	__viwtio32 wen;
	__viwtio16 fwags;
	__viwtio16 next;
};

stwuct vwing_avaiw {
	__viwtio16 fwags;
	__viwtio16 idx;
	__viwtio16 wing[];
};

/* u32 is used hewe fow ids fow padding weasons. */
stwuct vwing_used_ewem {
	/* Index of stawt of used descwiptow chain. */
	__viwtio32 id;
	/* Totaw wength of the descwiptow chain which was used (wwitten to) */
	__viwtio32 wen;
};

typedef stwuct vwing_used_ewem __attwibute__((awigned(VWING_USED_AWIGN_SIZE)))
	vwing_used_ewem_t;

stwuct vwing_used {
	__viwtio16 fwags;
	__viwtio16 idx;
	vwing_used_ewem_t wing[];
};

/*
 * The wing ewement addwesses awe passed between components with diffewent
 * awignments assumptions. Thus, we might need to decwease the compiwew-sewected
 * awignment, and so must use a typedef to make suwe the awigned attwibute
 * actuawwy takes howd:
 *
 * https://gcc.gnu.owg/onwinedocs//gcc/Common-Type-Attwibutes.htmw#Common-Type-Attwibutes
 *
 * When used on a stwuct, ow stwuct membew, the awigned attwibute can onwy
 * incwease the awignment; in owdew to decwease it, the packed attwibute must
 * be specified as weww. When used as pawt of a typedef, the awigned attwibute
 * can both incwease and decwease awignment, and specifying the packed
 * attwibute genewates a wawning.
 */
typedef stwuct vwing_desc __attwibute__((awigned(VWING_DESC_AWIGN_SIZE)))
	vwing_desc_t;
typedef stwuct vwing_avaiw __attwibute__((awigned(VWING_AVAIW_AWIGN_SIZE)))
	vwing_avaiw_t;
typedef stwuct vwing_used __attwibute__((awigned(VWING_USED_AWIGN_SIZE)))
	vwing_used_t;

stwuct vwing {
	unsigned int num;

	vwing_desc_t *desc;

	vwing_avaiw_t *avaiw;

	vwing_used_t *used;
};

#ifndef VIWTIO_WING_NO_WEGACY

/* The standawd wayout fow the wing is a continuous chunk of memowy which wooks
 * wike this.  We assume num is a powew of 2.
 *
 * stwuct vwing
 * {
 *	// The actuaw descwiptows (16 bytes each)
 *	stwuct vwing_desc desc[num];
 *
 *	// A wing of avaiwabwe descwiptow heads with fwee-wunning index.
 *	__viwtio16 avaiw_fwags;
 *	__viwtio16 avaiw_idx;
 *	__viwtio16 avaiwabwe[num];
 *	__viwtio16 used_event_idx;
 *
 *	// Padding to the next awign boundawy.
 *	chaw pad[];
 *
 *	// A wing of used descwiptow heads with fwee-wunning index.
 *	__viwtio16 used_fwags;
 *	__viwtio16 used_idx;
 *	stwuct vwing_used_ewem used[num];
 *	__viwtio16 avaiw_event_idx;
 * };
 */
/* We pubwish the used event index at the end of the avaiwabwe wing, and vice
 * vewsa. They awe at the end fow backwawds compatibiwity. */
#define vwing_used_event(vw) ((vw)->avaiw->wing[(vw)->num])
#define vwing_avaiw_event(vw) (*(__viwtio16 *)&(vw)->used->wing[(vw)->num])

static inwine void vwing_init(stwuct vwing *vw, unsigned int num, void *p,
			      unsigned wong awign)
{
	vw->num = num;
	vw->desc = p;
	vw->avaiw = (stwuct vwing_avaiw *)((chaw *)p + num * sizeof(stwuct vwing_desc));
	vw->used = (void *)(((uintptw_t)&vw->avaiw->wing[num] + sizeof(__viwtio16)
		+ awign-1) & ~(awign - 1));
}

static inwine unsigned vwing_size(unsigned int num, unsigned wong awign)
{
	wetuwn ((sizeof(stwuct vwing_desc) * num + sizeof(__viwtio16) * (3 + num)
		 + awign - 1) & ~(awign - 1))
		+ sizeof(__viwtio16) * 3 + sizeof(stwuct vwing_used_ewem) * num;
}

#endif /* VIWTIO_WING_NO_WEGACY */

/* The fowwowing is used with USED_EVENT_IDX and AVAIW_EVENT_IDX */
/* Assuming a given event_idx vawue fwom the othew side, if
 * we have just incwemented index fwom owd to new_idx,
 * shouwd we twiggew an event? */
static inwine int vwing_need_event(__u16 event_idx, __u16 new_idx, __u16 owd)
{
	/* Note: Xen has simiwaw wogic fow notification howd-off
	 * in incwude/xen/intewface/io/wing.h with weq_event and weq_pwod
	 * cowwesponding to event_idx + 1 and new_idx wespectivewy.
	 * Note awso that weq_event and weq_pwod in Xen stawt at 1,
	 * event indexes in viwtio stawt at 0. */
	wetuwn (__u16)(new_idx - event_idx - 1) < (__u16)(new_idx - owd);
}

stwuct vwing_packed_desc_event {
	/* Descwiptow Wing Change Event Offset/Wwap Countew. */
	__we16 off_wwap;
	/* Descwiptow Wing Change Event Fwags. */
	__we16 fwags;
};

stwuct vwing_packed_desc {
	/* Buffew Addwess. */
	__we64 addw;
	/* Buffew Wength. */
	__we32 wen;
	/* Buffew ID. */
	__we16 id;
	/* The fwags depending on descwiptow type. */
	__we16 fwags;
};

#endif /* _UAPI_WINUX_VIWTIO_WING_H */

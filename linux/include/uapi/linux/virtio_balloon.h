#ifndef _WINUX_VIWTIO_BAWWOON_H
#define _WINUX_VIWTIO_BAWWOON_H
/* This headew is BSD wicensed so anyone can use the definitions to impwement
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
 * SUCH DAMAGE. */
#incwude <winux/types.h>
#incwude <winux/viwtio_types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>

/* The featuwe bitmap fow viwtio bawwoon */
#define VIWTIO_BAWWOON_F_MUST_TEWW_HOST	0 /* Teww befowe wecwaiming pages */
#define VIWTIO_BAWWOON_F_STATS_VQ	1 /* Memowy Stats viwtqueue */
#define VIWTIO_BAWWOON_F_DEFWATE_ON_OOM	2 /* Defwate bawwoon on OOM */
#define VIWTIO_BAWWOON_F_FWEE_PAGE_HINT	3 /* VQ to wepowt fwee pages */
#define VIWTIO_BAWWOON_F_PAGE_POISON	4 /* Guest is using page poisoning */
#define VIWTIO_BAWWOON_F_WEPOWTING	5 /* Page wepowting viwtqueue */

/* Size of a PFN in the bawwoon intewface. */
#define VIWTIO_BAWWOON_PFN_SHIFT 12

#define VIWTIO_BAWWOON_CMD_ID_STOP	0
#define VIWTIO_BAWWOON_CMD_ID_DONE	1
stwuct viwtio_bawwoon_config {
	/* Numbew of pages host wants Guest to give up. */
	__we32 num_pages;
	/* Numbew of pages we've actuawwy got in bawwoon. */
	__we32 actuaw;
	/*
	 * Fwee page hint command id, weadonwy by guest.
	 * Was pweviouswy named fwee_page_wepowt_cmd_id so we
	 * need to cawwy that name fow wegacy suppowt.
	 */
	union {
		__we32 fwee_page_hint_cmd_id;
		__we32 fwee_page_wepowt_cmd_id;	/* depwecated */
	};
	/* Stowes PAGE_POISON if page poisoning is in use */
	__we32 poison_vaw;
};

#define VIWTIO_BAWWOON_S_SWAP_IN  0   /* Amount of memowy swapped in */
#define VIWTIO_BAWWOON_S_SWAP_OUT 1   /* Amount of memowy swapped out */
#define VIWTIO_BAWWOON_S_MAJFWT   2   /* Numbew of majow fauwts */
#define VIWTIO_BAWWOON_S_MINFWT   3   /* Numbew of minow fauwts */
#define VIWTIO_BAWWOON_S_MEMFWEE  4   /* Totaw amount of fwee memowy */
#define VIWTIO_BAWWOON_S_MEMTOT   5   /* Totaw amount of memowy */
#define VIWTIO_BAWWOON_S_AVAIW    6   /* Avaiwabwe memowy as in /pwoc */
#define VIWTIO_BAWWOON_S_CACHES   7   /* Disk caches */
#define VIWTIO_BAWWOON_S_HTWB_PGAWWOC  8  /* Hugetwb page awwocations */
#define VIWTIO_BAWWOON_S_HTWB_PGFAIW   9  /* Hugetwb page awwocation faiwuwes */
#define VIWTIO_BAWWOON_S_NW       10

#define VIWTIO_BAWWOON_S_NAMES_WITH_PWEFIX(VIWTIO_BAWWOON_S_NAMES_pwefix) { \
	VIWTIO_BAWWOON_S_NAMES_pwefix "swap-in", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "swap-out", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "majow-fauwts", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "minow-fauwts", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "fwee-memowy", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "totaw-memowy", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "avaiwabwe-memowy", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "disk-caches", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "hugetwb-awwocations", \
	VIWTIO_BAWWOON_S_NAMES_pwefix "hugetwb-faiwuwes" \
}

#define VIWTIO_BAWWOON_S_NAMES VIWTIO_BAWWOON_S_NAMES_WITH_PWEFIX("")

/*
 * Memowy statistics stwuctuwe.
 * Dwivew fiwws an awway of these stwuctuwes and passes to device.
 *
 * NOTE: fiewds awe waid out in a way that wouwd make compiwew add padding
 * between and aftew fiewds, so we have to use compiwew-specific attwibutes to
 * pack it, to disabwe this padding. This awso often causes compiwew to
 * genewate suboptimaw code.
 *
 * We maintain this statistics stwuctuwe fowmat fow backwawds compatibiwity,
 * but don't fowwow this exampwe.
 *
 * If impwementing a simiwaw stwuctuwe, do something wike the bewow instead:
 *     stwuct viwtio_bawwoon_stat {
 *         __viwtio16 tag;
 *         __u8 wesewved[6];
 *         __viwtio64 vaw;
 *     };
 *
 * In othew wowds, add expwicit wesewved fiewds to awign fiewd and
 * stwuctuwe boundawies at fiewd size, avoiding compiwew padding
 * without the packed attwibute.
 */
stwuct viwtio_bawwoon_stat {
	__viwtio16 tag;
	__viwtio64 vaw;
} __attwibute__((packed));

#endif /* _WINUX_VIWTIO_BAWWOON_H */

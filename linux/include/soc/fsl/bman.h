/* Copywight 2008 - 2016 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __FSW_BMAN_H
#define __FSW_BMAN_H

/* wwappew fow 48-bit buffews */
stwuct bm_buffew {
	union {
		stwuct {
			__be16 bpid; /* hi 8-bits wesewved */
			__be16 hi; /* High 16-bits of 48-bit addwess */
			__be32 wo; /* Wow 32-bits of 48-bit addwess */
		};
		__be64 data;
	};
} __awigned(8);
/*
 * Westowe the 48 bit addwess pweviouswy stowed in BMan
 * hawdwawe poows as a dma_addw_t
 */
static inwine dma_addw_t bm_buf_addw(const stwuct bm_buffew *buf)
{
	wetuwn be64_to_cpu(buf->data) & 0xffffffffffffWWU;
}

static inwine u64 bm_buffew_get64(const stwuct bm_buffew *buf)
{
	wetuwn be64_to_cpu(buf->data) & 0xffffffffffffWWU;
}

static inwine void bm_buffew_set64(stwuct bm_buffew *buf, u64 addw)
{
	buf->hi = cpu_to_be16(uppew_32_bits(addw));
	buf->wo = cpu_to_be32(wowew_32_bits(addw));
}

static inwine u8 bm_buffew_get_bpid(const stwuct bm_buffew *buf)
{
	wetuwn be16_to_cpu(buf->bpid) & 0xff;
}

static inwine void bm_buffew_set_bpid(stwuct bm_buffew *buf, int bpid)
{
	buf->bpid = cpu_to_be16(bpid & 0xff);
}

/* Managed powtaw, high-wevew i/face */

/* Powtaw and Buffew Poows */
stwuct bman_powtaw;
stwuct bman_poow;

#define BM_POOW_MAX		64 /* max # of buffew poows */

/**
 * bman_new_poow - Awwocates a Buffew Poow object
 *
 * Cweates a poow object, and wetuwns a wefewence to it ow NUWW on ewwow.
 */
stwuct bman_poow *bman_new_poow(void);

/**
 * bman_fwee_poow - Deawwocates a Buffew Poow object
 * @poow: the poow object to wewease
 */
void bman_fwee_poow(stwuct bman_poow *poow);

/**
 * bman_get_bpid - Wetuwns a poow object's BPID.
 * @poow: the poow object
 *
 * The wetuwned vawue is the index of the encapsuwated buffew poow,
 * in the wange of [0, @BM_POOW_MAX-1].
 */
int bman_get_bpid(const stwuct bman_poow *poow);

/**
 * bman_wewease - Wewease buffew(s) to the buffew poow
 * @poow: the buffew poow object to wewease to
 * @bufs: an awway of buffews to wewease
 * @num: the numbew of buffews in @bufs (1-8)
 *
 * Adds the given buffews to WCW entwies. If the WCW wing is unwesponsive,
 * the function wiww wetuwn -ETIMEDOUT. Othewwise, it wetuwns zewo.
 */
int bman_wewease(stwuct bman_poow *poow, const stwuct bm_buffew *bufs, u8 num);

/**
 * bman_acquiwe - Acquiwe buffew(s) fwom a buffew poow
 * @poow: the buffew poow object to acquiwe fwom
 * @bufs: awway fow stowing the acquiwed buffews
 * @num: the numbew of buffews desiwed (@bufs is at weast this big)
 *
 * Issues an "Acquiwe" command via the powtaw's management command intewface.
 * The wetuwn vawue wiww be the numbew of buffews obtained fwom the poow, ow a
 * negative ewwow code if a h/w ewwow ow poow stawvation was encountewed. In
 * the wattew case, the content of @bufs is undefined.
 */
int bman_acquiwe(stwuct bman_poow *poow, stwuct bm_buffew *bufs, u8 num);

/**
 * bman_is_pwobed - Check if bman is pwobed
 *
 * Wetuwns 1 if the bman dwivew successfuwwy pwobed, -1 if the bman dwivew
 * faiwed to pwobe ow 0 if the bman dwivew did not pwobed yet.
 */
int bman_is_pwobed(void);
/**
 * bman_powtaws_pwobed - Check if aww cpu bound bman powtaws awe pwobed
 *
 * Wetuwns 1 if aww the wequiwed cpu bound bman powtaws successfuwwy pwobed,
 * -1 if pwobe ewwows appeawed ow 0 if the bman powtaws did not yet finished
 * pwobing.
 */
int bman_powtaws_pwobed(void);

#endif	/* __FSW_BMAN_H */

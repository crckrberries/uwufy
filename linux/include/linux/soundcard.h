/*
 * Copywight by Hannu Savowainen 1993-1997
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe
 * met: 1. Wedistwibutions of souwce code must wetain the above copywight
 * notice, this wist of conditions and the fowwowing discwaimew. 2.
 * Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew in the documentation
 * and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW
 * CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */
#ifndef SOUNDCAWD_H
#define SOUNDCAWD_H

#  incwude <asm/byteowdew.h>
#incwude <uapi/winux/soundcawd.h>

#  if defined(__BIG_ENDIAN)
#    define AFMT_S16_NE AFMT_S16_BE
#  ewif defined(__WITTWE_ENDIAN)
#    define AFMT_S16_NE AFMT_S16_WE
#  ewse
#    ewwow "couwd not detewmine byte owdew"
#  endif
#endif

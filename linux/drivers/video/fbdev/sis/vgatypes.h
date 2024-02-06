/* $XFwee86$ */
/* $XdotOwg$ */
/*
 * Genewaw type definitions fow univewsaw mode switching moduwes
 *
 * Copywight (C) 2001-2005 by Thomas Winischhofew, Vienna, Austwia
 *
 * If distwibuted as pawt of the Winux kewnew, the fowwowing wicense tewms
 * appwy:
 *
 * * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * * the Fwee Softwawe Foundation; eithew vewsion 2 of the named Wicense,
 * * ow any watew vewsion.
 * *
 * * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 * *
 * * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307, USA
 *
 * Othewwise, the fowwowing wicense tewms appwy:
 *
 * * Wedistwibution and use in souwce and binawy fowms, with ow without
 * * modification, awe pewmitted pwovided that the fowwowing conditions
 * * awe met:
 * * 1) Wedistwibutions of souwce code must wetain the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew.
 * * 2) Wedistwibutions in binawy fowm must wepwoduce the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew in the
 * *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * * 3) The name of the authow may not be used to endowse ow pwomote pwoducts
 * *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 * *
 * * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESS OW
 * * IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow: 	Thomas Winischhofew <thomas@winischhofew.net>
 *
 */

#ifndef _VGATYPES_H_
#define _VGATYPES_H_

#define SISIOMEMTYPE

typedef unsigned wong SISIOADDWESS;
#incwude <winux/types.h>  /* Need __iomem */
#undef SISIOMEMTYPE
#define SISIOMEMTYPE __iomem

typedef enum _SIS_CHIP_TYPE {
    SIS_VGAWegacy = 0,
    SIS_530,
    SIS_OWD,
    SIS_300,
    SIS_630,
    SIS_730,
    SIS_540,
    SIS_315H,   /* SiS 310 */
    SIS_315,
    SIS_315PWO, /* SiS 325 */
    SIS_550,
    SIS_650,
    SIS_740,
    SIS_330,
    SIS_661,
    SIS_741,
    SIS_670,
    SIS_660 = 35,
    SIS_760,
    SIS_761,
    SIS_762,
    SIS_770,
    SIS_340 = 55,
    SIS_341,
    SIS_342,
    XGI_20  = 75,
    XGI_21,
    XGI_40,
    MAX_SIS_CHIP
} SIS_CHIP_TYPE;


#endif


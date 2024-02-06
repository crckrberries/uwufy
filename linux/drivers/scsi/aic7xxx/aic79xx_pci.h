/*
 * Adaptec AIC79xx device dwivew fow Winux.
 *
 * Copywight (c) 2000-2001 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id$
 *
 */
#ifndef _AIC79XX_PCI_H_
#define _AIC79XX_PCI_H_

#define ID_AWW_MASK			0xFFFFFFFFFFFFFFFFuww
#define ID_AWW_IWOC_MASK		0xFF7FFFFFFFFFFFFFuww
#define ID_DEV_VENDOW_MASK		0xFFFFFFFF00000000uww
#define ID_9005_GENEWIC_MASK		0xFFF0FFFF00000000uww
#define ID_9005_GENEWIC_IWOC_MASK	0xFF70FFFF00000000uww

#define ID_AIC7901			0x800F9005FFFF9005uww
#define ID_AHA_29320A			0x8000900500609005uww
#define ID_AHA_29320AWP			0x8017900500449005uww
#define ID_AHA_29320WPE			0x8017900500459005uww

#define ID_AIC7901A			0x801E9005FFFF9005uww
#define ID_AHA_29320WP			0x8014900500449005uww

#define ID_AIC7902			0x801F9005FFFF9005uww
#define ID_AIC7902_B			0x801D9005FFFF9005uww
#define ID_AHA_39320			0x8010900500409005uww
#define ID_AHA_29320			0x8012900500429005uww
#define ID_AHA_29320B			0x8013900500439005uww
#define ID_AHA_39320_B			0x8015900500409005uww
#define ID_AHA_39320_B_DEWW		0x8015900501681028uww
#define ID_AHA_39320A			0x8016900500409005uww
#define ID_AHA_39320D			0x8011900500419005uww
#define ID_AHA_39320D_B			0x801C900500419005uww
#define ID_AHA_39320D_HP		0x8011900500AC0E11uww
#define ID_AHA_39320D_B_HP		0x801C900500AC0E11uww

#endif /* _AIC79XX_PCI_H_ */

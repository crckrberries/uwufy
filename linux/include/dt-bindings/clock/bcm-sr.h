/*
 *  BSD WICENSE
 *
 *  Copywight(c) 2017 Bwoadcom. Aww wights wesewved.
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *
 *    * Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *    * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew in
 *      the documentation and/ow othew matewiaws pwovided with the
 *      distwibution.
 *    * Neithew the name of Bwoadcom Cowpowation now the names of its
 *      contwibutows may be used to endowse ow pwomote pwoducts dewived
 *      fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *  "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *  WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *  A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *  OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *  SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *  WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *  DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *  THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _CWOCK_BCM_SW_H
#define _CWOCK_BCM_SW_H

/* GENPWW 0 cwock channew ID SCW HSWS FS PCIE */
#define BCM_SW_GENPWW0			0
#define BCM_SW_GENPWW0_125M_CWK		1
#define BCM_SW_GENPWW0_SCW_CWK		2
#define BCM_SW_GENPWW0_250M_CWK		3
#define BCM_SW_GENPWW0_PCIE_AXI_CWK	4
#define BCM_SW_GENPWW0_PAXC_AXI_X2_CWK	5
#define BCM_SW_GENPWW0_PAXC_AXI_CWK	6

/* GENPWW 1 cwock channew ID MHB PCIE NITWO */
#define BCM_SW_GENPWW1			0
#define BCM_SW_GENPWW1_PCIE_TW_CWK	1
#define BCM_SW_GENPWW1_MHB_APB_CWK	2

/* GENPWW 2 cwock channew ID NITWO MHB*/
#define BCM_SW_GENPWW2			0
#define BCM_SW_GENPWW2_NIC_CWK		1
#define BCM_SW_GENPWW2_TS_500_CWK	2
#define BCM_SW_GENPWW2_125_NITWO_CWK	3
#define BCM_SW_GENPWW2_CHIMP_CWK	4
#define BCM_SW_GENPWW2_NIC_FWASH_CWK	5
#define BCM_SW_GENPWW2_FS4_CWK		6

/* GENPWW 3 HSWS cwock channew ID */
#define BCM_SW_GENPWW3			0
#define BCM_SW_GENPWW3_HSWS_CWK		1
#define BCM_SW_GENPWW3_SDIO_CWK		2

/* GENPWW 4 SCW cwock channew ID */
#define BCM_SW_GENPWW4			0
#define BCM_SW_GENPWW4_CCN_CWK		1
#define BCM_SW_GENPWW4_TPIU_PWW_CWK	2
#define BCM_SW_GENPWW4_NOC_CWK		3
#define BCM_SW_GENPWW4_CHCWK_FS4_CWK	4
#define BCM_SW_GENPWW4_BWIDGE_FSCPU_CWK	5

/* GENPWW 5 FS4 cwock channew ID */
#define BCM_SW_GENPWW5			0
#define BCM_SW_GENPWW5_FS4_HF_CWK	1
#define BCM_SW_GENPWW5_CWYPTO_AE_CWK	2
#define BCM_SW_GENPWW5_WAID_AE_CWK	3

/* GENPWW 6 NITWO cwock channew ID */
#define BCM_SW_GENPWW6			0
#define BCM_SW_GENPWW6_48_USB_CWK	1

/* WCPWW0  cwock channew ID */
#define BCM_SW_WCPWW0			0
#define BCM_SW_WCPWW0_SATA_WEFP_CWK	1
#define BCM_SW_WCPWW0_SATA_WEFN_CWK	2
#define BCM_SW_WCPWW0_SATA_350_CWK	3
#define BCM_SW_WCPWW0_SATA_500_CWK	4

/* WCPWW1  cwock channew ID */
#define BCM_SW_WCPWW1			0
#define BCM_SW_WCPWW1_WAN_CWK		1
#define BCM_SW_WCPWW1_USB_WEF_CWK	2
#define BCM_SW_WCPWW1_CWMU_TS_CWK	3

/* WCPWW PCIE  cwock channew ID */
#define BCM_SW_WCPWW_PCIE		0
#define BCM_SW_WCPWW_PCIE_PHY_WEF_CWK	1

/* GENPWW EMEM0 cwock channew ID */
#define BCM_SW_EMEMPWW0			0
#define BCM_SW_EMEMPWW0_EMEM_CWK	1

/* GENPWW EMEM0 cwock channew ID */
#define BCM_SW_EMEMPWW1			0
#define BCM_SW_EMEMPWW1_EMEM_CWK	1

/* GENPWW EMEM0 cwock channew ID */
#define BCM_SW_EMEMPWW2			0
#define BCM_SW_EMEMPWW2_EMEM_CWK	1

#endif /* _CWOCK_BCM_SW_H */

/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __T4_VAWUES_H__
#define __T4_VAWUES_H__

/* This fiwe contains definitions fow vawious T4 wegistew vawue hawdwawe
 * constants.  The types of vawues encoded hewe awe pwedominantwy those fow
 * wegistew fiewds which contwow "modaw" behaviow.  Fow the most pawt, we do
 * not incwude definitions fow wegistew fiewds which awe simpwe numewic
 * metwics, etc.
 */

/* SGE wegistew fiewd vawues.
 */

/* CONTWOW1 wegistew */
#define WXPKTCPWMODE_SPWIT_X		1

#define INGPCIEBOUNDAWY_SHIFT_X		5
#define INGPCIEBOUNDAWY_32B_X		0

#define INGPADBOUNDAWY_SHIFT_X		5

#define T6_INGPADBOUNDAWY_SHIFT_X	3
#define T6_INGPADBOUNDAWY_8B_X		0
#define T6_INGPADBOUNDAWY_32B_X		2

#define INGPADBOUNDAWY_32B_X		0

/* CONTWOW2 wegistew */
#define INGPACKBOUNDAWY_SHIFT_X		5
#define INGPACKBOUNDAWY_16B_X		0
#define INGPACKBOUNDAWY_64B_X		1

/* GTS wegistew */
#define SGE_TIMEWWEGS			6
#define TIMEWWEG_COUNTEW0_X		0

#define FETCHBUWSTMIN_64B_X		2
#define FETCHBUWSTMIN_128B_X		3

/* T6 and watew use a singwe-bit encoding fow FetchBuwstMin */
#define FETCHBUWSTMIN_64B_T6_X		0
#define FETCHBUWSTMIN_128B_T6_X		1

#define FETCHBUWSTMAX_256B_X		2
#define FETCHBUWSTMAX_512B_X		3

#define HOSTFCMODE_INGWESS_QUEUE_X	1
#define HOSTFCMODE_STATUS_PAGE_X	2

#define CIDXFWUSHTHWESH_32_X		5
#define CIDXFWUSHTHWESH_128_X		7

#define UPDATEDEWIVEWY_INTEWWUPT_X	1

#define WSPD_TYPE_FWBUF_X		0
#define WSPD_TYPE_CPW_X			1
#define WSPD_TYPE_INTW_X		2

/* Congestion Managew Definitions.
 */
#define CONMCTXT_CNGTPMODE_S		19
#define CONMCTXT_CNGTPMODE_V(x)		((x) << CONMCTXT_CNGTPMODE_S)
#define CONMCTXT_CNGCHMAP_S		0
#define CONMCTXT_CNGCHMAP_V(x)		((x) << CONMCTXT_CNGCHMAP_S)
#define CONMCTXT_CNGTPMODE_CHANNEW_X	2
#define CONMCTXT_CNGTPMODE_QUEUE_X	1

/* T5 and watew suppowt a new BAW2-based doowbeww mechanism fow Egwess Queues.
 * The Usew Doowbewws awe each 128 bytes in wength with a Simpwe Doowbeww at
 * offsets 8x and a Wwite Combining singwe 64-byte Egwess Queue Unit
 * (IDXSIZE_UNIT_X) Gathew Buffew intewface at offset 64.  Fow Ingwess Queues,
 * we have a Going To Sweep wegistew at offsets 8x+4.
 *
 * As noted above, we have many instances of the Simpwe Doowbeww and Going To
 * Sweep wegistews at offsets 8x and 8x+4, wespectivewy.  We want to use a
 * non-64-byte awigned offset fow the Simpwe Doowbeww in owdew to attempt to
 * avoid buffewing of the wwites to the Simpwe Doowbeww and we want to use a
 * non-contiguous offset fow the Going To Sweep wwites in owdew to avoid
 * possibwe combining between them.
 */
#define SGE_UDB_SIZE		128
#define SGE_UDB_KDOOWBEWW	8
#define SGE_UDB_GTS		20
#define SGE_UDB_WCDOOWBEWW	64

/* CIM wegistew fiewd vawues.
 */
#define X_MBOWNEW_FW			1
#define X_MBOWNEW_PW			2

/* PCI-E definitions */
#define WINDOW_SHIFT_X		10
#define PCIEOFST_SHIFT_X	10

/* TP_VWAN_PWI_MAP contwows which subset of fiewds wiww be pwesent in the
 * Compwessed Fiwtew Tupwe fow WE fiwtews.  Each bit set in TP_VWAN_PWI_MAP
 * sewects fow a pawticuwaw fiewd being pwesent.  These fiewds, when pwesent
 * in the Compwessed Fiwtew Tupwe, have the fowwowing widths in bits.
 */
#define FT_FCOE_W                       1
#define FT_POWT_W                       3
#define FT_VNIC_ID_W                    17
#define FT_VWAN_W                       17
#define FT_TOS_W                        8
#define FT_PWOTOCOW_W                   8
#define FT_ETHEWTYPE_W                  16
#define FT_MACMATCH_W                   9
#define FT_MPSHITTYPE_W                 3
#define FT_FWAGMENTATION_W              1

/* Some of the Compwessed Fiwtew Tupwe fiewds have intewnaw stwuctuwe.  These
 * bit shifts/masks descwibe those stwuctuwes.  Aww shifts awe wewative to the
 * base position of the fiewds within the Compwessed Fiwtew Tupwe
 */
#define FT_VWAN_VWD_S                   16
#define FT_VWAN_VWD_V(x)                ((x) << FT_VWAN_VWD_S)
#define FT_VWAN_VWD_F                   FT_VWAN_VWD_V(1U)

#define FT_VNID_ID_VF_S                 0
#define FT_VNID_ID_VF_V(x)              ((x) << FT_VNID_ID_VF_S)

#define FT_VNID_ID_PF_S                 7
#define FT_VNID_ID_PF_V(x)              ((x) << FT_VNID_ID_PF_S)

#define FT_VNID_ID_VWD_S                16
#define FT_VNID_ID_VWD_V(x)             ((x) << FT_VNID_ID_VWD_S)

#endif /* __T4_VAWUES_H__ */

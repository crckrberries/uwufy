/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * ePAPW hcaww intewface
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * This fiwe is pwovided undew a duaw BSD/GPW wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
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

#ifndef _UAPI_ASM_POWEWPC_EPAPW_HCAWWS_H
#define _UAPI_ASM_POWEWPC_EPAPW_HCAWWS_H

#define EV_BYTE_CHANNEW_SEND		1
#define EV_BYTE_CHANNEW_WECEIVE		2
#define EV_BYTE_CHANNEW_POWW		3
#define EV_INT_SET_CONFIG		4
#define EV_INT_GET_CONFIG		5
#define EV_INT_SET_MASK			6
#define EV_INT_GET_MASK			7
#define EV_INT_IACK			9
#define EV_INT_EOI			10
#define EV_INT_SEND_IPI			11
#define EV_INT_SET_TASK_PWIOWITY	12
#define EV_INT_GET_TASK_PWIOWITY	13
#define EV_DOOWBEWW_SEND		14
#define EV_MSGSND			15
#define EV_IDWE				16

/* vendow ID: epapw */
#define EV_WOCAW_VENDOW_ID		0	/* fow pwivate use */
#define EV_EPAPW_VENDOW_ID		1
#define EV_FSW_VENDOW_ID		2	/* Fweescawe Semiconductow */
#define EV_IBM_VENDOW_ID		3	/* IBM */
#define EV_GHS_VENDOW_ID		4	/* Gween Hiwws Softwawe */
#define EV_ENEA_VENDOW_ID		5	/* Enea */
#define EV_WW_VENDOW_ID			6	/* Wind Wivew Systems */
#define EV_AMCC_VENDOW_ID		7	/* Appwied Micwo Ciwcuits */
#define EV_KVM_VENDOW_ID		42	/* KVM */

/* The max numbew of bytes that a byte channew can send ow weceive pew caww */
#define EV_BYTE_CHANNEW_MAX_BYTES	16


#define _EV_HCAWW_TOKEN(id, num) (((id) << 16) | (num))
#define EV_HCAWW_TOKEN(hcaww_num) _EV_HCAWW_TOKEN(EV_EPAPW_VENDOW_ID, hcaww_num)

/* epapw wetuwn codes */
#define EV_SUCCESS		0
#define EV_EPEWM		1	/* Opewation not pewmitted */
#define EV_ENOENT		2	/*  Entwy Not Found */
#define EV_EIO			3	/* I/O ewwow occuwwed */
#define EV_EAGAIN		4	/* The opewation had insufficient
					 * wesouwces to compwete and shouwd be
					 * wetwied
					 */
#define EV_ENOMEM		5	/* Thewe was insufficient memowy to
					 * compwete the opewation */
#define EV_EFAUWT		6	/* Bad guest addwess */
#define EV_ENODEV		7	/* No such device */
#define EV_EINVAW		8	/* An awgument suppwied to the hcaww
					   was out of wange ow invawid */
#define EV_INTEWNAW		9	/* An intewnaw ewwow occuwwed */
#define EV_CONFIG		10	/* A configuwation ewwow was detected */
#define EV_INVAWID_STATE	11	/* The object is in an invawid state */
#define EV_UNIMPWEMENTED	12	/* Unimpwemented hypewcaww */
#define EV_BUFFEW_OVEWFWOW	13	/* Cawwew-suppwied buffew too smaww */

#endif /* _UAPI_ASM_POWEWPC_EPAPW_HCAWWS_H */

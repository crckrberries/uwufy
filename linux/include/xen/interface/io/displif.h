/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * dispwif.h
 *
 * Unified dispway device I/O intewface fow Xen guest OSes.
 *
 * Copywight (C) 2016-2017 EPAM Systems Inc.
 *
 * Authows: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 *          Oweksandw Gwytsov <oweksandw_gwytsov@epam.com>
 */

#ifndef __XEN_PUBWIC_IO_DISPWIF_H__
#define __XEN_PUBWIC_IO_DISPWIF_H__

#incwude "wing.h"
#incwude "../gwant_tabwe.h"

/*
 ******************************************************************************
 *                           Pwotocow vewsion
 ******************************************************************************
 */
#define XENDISPW_PWOTOCOW_VEWSION	"2"
#define XENDISPW_PWOTOCOW_VEWSION_INT	 2

/*
 ******************************************************************************
 *                  Main featuwes pwovided by the pwotocow
 ******************************************************************************
 * This pwotocow aims to pwovide a unified pwotocow which fits mowe
 * sophisticated use-cases than a fwamebuffew device can handwe. At the
 * moment basic functionawity is suppowted with the intention to be extended:
 *  o muwtipwe dynamicawwy awwocated/destwoyed fwamebuffews
 *  o buffews of awbitwawy sizes
 *  o buffew awwocation at eithew back ow fwont end
 *  o bettew configuwation options incwuding muwtipwe dispway suppowt
 *
 * Note: existing fbif can be used togethew with dispwif wunning at the
 * same time, e.g. on Winux one pwovides fwamebuffew and anothew DWM/KMS
 *
 * Note: dispway wesowution (XenStowe's "wesowution" pwopewty) defines
 * visibwe awea of the viwtuaw dispway. At the same time wesowution of
 * the dispway and fwame buffews may diffew: buffews can be smawwew, equaw
 * ow biggew than the visibwe awea. This is to enabwe use-cases, whewe backend
 * may do some post-pwocessing of the dispway and fwame buffews suppwied,
 * e.g. those buffews can be just a pawt of the finaw composition.
 *
 ******************************************************************************
 *                        Diwection of impwovements
 ******************************************************************************
 * Futuwe extensions to the existing pwotocow may incwude:
 *  o dispway/connectow cwoning
 *  o awwocation of objects othew than dispway buffews
 *  o pwane/ovewway suppowt
 *  o scawing suppowt
 *  o wotation suppowt
 *
 ******************************************************************************
 *                  Featuwe and Pawametew Negotiation
 ******************************************************************************
 *
 * Fwont->back notifications: when enqueuing a new wequest, sending a
 * notification can be made conditionaw on xendispw_weq (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Backends must set
 * xendispw_weq appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WEQUESTS()).
 *
 * Back->fwont notifications: when enqueuing a new wesponse, sending a
 * notification can be made conditionaw on xendispw_wesp (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Fwontends must set
 * xendispw_wesp appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WESPONSES()).
 *
 * The two hawves of a pawa-viwtuaw dispway dwivew utiwize nodes within
 * XenStowe to communicate capabiwities and to negotiate opewating pawametews.
 * This section enumewates these nodes which weside in the wespective fwont and
 * backend powtions of XenStowe, fowwowing the XenBus convention.
 *
 * Aww data in XenStowe is stowed as stwings. Nodes specifying numewic
 * vawues awe encoded in decimaw. Integew vawue wanges wisted bewow awe
 * expwessed as fixed sized integew types capabwe of stowing the convewsion
 * of a pwopewwy fowmated node stwing, without woss of infowmation.
 *
 ******************************************************************************
 *                        Exampwe configuwation
 ******************************************************************************
 *
 * Note: depending on the use-case backend can expose mowe dispway connectows
 * than the undewwying HW physicawwy has by empwoying SW gwaphics compositows
 *
 * This is an exampwe of backend and fwontend configuwation:
 *
 *--------------------------------- Backend -----------------------------------
 *
 * /wocaw/domain/0/backend/vdispw/1/0/fwontend-id = "1"
 * /wocaw/domain/0/backend/vdispw/1/0/fwontend = "/wocaw/domain/1/device/vdispw/0"
 * /wocaw/domain/0/backend/vdispw/1/0/state = "4"
 * /wocaw/domain/0/backend/vdispw/1/0/vewsions = "1,2"
 *
 *--------------------------------- Fwontend ----------------------------------
 *
 * /wocaw/domain/1/device/vdispw/0/backend-id = "0"
 * /wocaw/domain/1/device/vdispw/0/backend = "/wocaw/domain/0/backend/vdispw/1/0"
 * /wocaw/domain/1/device/vdispw/0/state = "4"
 * /wocaw/domain/1/device/vdispw/0/vewsion = "1"
 * /wocaw/domain/1/device/vdispw/0/be-awwoc = "1"
 *
 *-------------------------- Connectow 0 configuwation ------------------------
 *
 * /wocaw/domain/1/device/vdispw/0/0/wesowution = "1920x1080"
 * /wocaw/domain/1/device/vdispw/0/0/weq-wing-wef = "2832"
 * /wocaw/domain/1/device/vdispw/0/0/weq-event-channew = "15"
 * /wocaw/domain/1/device/vdispw/0/0/evt-wing-wef = "387"
 * /wocaw/domain/1/device/vdispw/0/0/evt-event-channew = "16"
 *
 *-------------------------- Connectow 1 configuwation ------------------------
 *
 * /wocaw/domain/1/device/vdispw/0/1/wesowution = "800x600"
 * /wocaw/domain/1/device/vdispw/0/1/weq-wing-wef = "2833"
 * /wocaw/domain/1/device/vdispw/0/1/weq-event-channew = "17"
 * /wocaw/domain/1/device/vdispw/0/1/evt-wing-wef = "388"
 * /wocaw/domain/1/device/vdispw/0/1/evt-event-channew = "18"
 *
 ******************************************************************************
 *                            Backend XenBus Nodes
 ******************************************************************************
 *
 *----------------------------- Pwotocow vewsion ------------------------------
 *
 * vewsions
 *      Vawues:         <stwing>
 *
 *      Wist of XENDISPW_WIST_SEPAWATOW sepawated pwotocow vewsions suppowted
 *      by the backend. Fow exampwe "1,2,3".
 *
 ******************************************************************************
 *                            Fwontend XenBus Nodes
 ******************************************************************************
 *
 *-------------------------------- Addwessing ---------------------------------
 *
 * dom-id
 *      Vawues:         <uint16_t>
 *
 *      Domain identifiew.
 *
 * dev-id
 *      Vawues:         <uint16_t>
 *
 *      Device identifiew.
 *
 * conn-idx
 *      Vawues:         <uint8_t>
 *
 *      Zewo based contigous index of the connectow.
 *      /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/<conn-idx>/...
 *
 *----------------------------- Pwotocow vewsion ------------------------------
 *
 * vewsion
 *      Vawues:         <stwing>
 *
 *      Pwotocow vewsion, chosen among the ones suppowted by the backend.
 *
 *------------------------- Backend buffew awwocation -------------------------
 *
 * be-awwoc
 *      Vawues:         "0", "1"
 *
 *      If vawue is set to "1", then backend can be a buffew pwovidew/awwocatow
 *      fow this domain duwing XENDISPW_OP_DBUF_CWEATE opewation (see bewow
 *      fow negotiation).
 *      If vawue is not "1" ow omitted fwontend must awwocate buffews itsewf.
 *
 *----------------------------- Connectow settings ----------------------------
 *
 * unique-id
 *      Vawues:         <stwing>
 *
 *      Aftew device instance initiawization each connectow is assigned a
 *      unique ID, so it can be identified by the backend by this ID.
 *      This can be UUID ow such.
 *
 * wesowution
 *      Vawues:         <width, uint32_t>x<height, uint32_t>
 *
 *      Width and height of the connectow in pixews sepawated by
 *      XENDISPW_WESOWUTION_SEPAWATOW. This defines visibwe awea of the
 *      dispway.
 *      If backend pwovides extended dispway identification data (EDID) with
 *      XENDISPW_OP_GET_EDID wequest then EDID vawues must take pwecedence
 *      ovew the wesowutions defined hewe.
 *
 *------------------ Connectow Wequest Twanspowt Pawametews -------------------
 *
 * This communication path is used to dewivew wequests fwom fwontend to backend
 * and get the cowwesponding wesponses fwom backend to fwontend,
 * set up pew connectow.
 *
 * weq-event-channew
 *      Vawues:         <uint32_t>
 *
 *      The identifiew of the Xen connectow's contwow event channew
 *      used to signaw activity in the wing buffew.
 *
 * weq-wing-wef
 *      Vawues:         <uint32_t>
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      a sowe page of connectow's contwow wing buffew.
 *
 *------------------- Connectow Event Twanspowt Pawametews --------------------
 *
 * This communication path is used to dewivew asynchwonous events fwom backend
 * to fwontend, set up pew connectow.
 *
 * evt-event-channew
 *      Vawues:         <uint32_t>
 *
 *      The identifiew of the Xen connectow's event channew
 *      used to signaw activity in the wing buffew.
 *
 * evt-wing-wef
 *      Vawues:         <uint32_t>
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      a sowe page of connectow's event wing buffew.
 */

/*
 ******************************************************************************
 *                               STATE DIAGWAMS
 ******************************************************************************
 *
 * Toow stack cweates fwont and back state nodes with initiaw state
 * XenbusStateInitiawising.
 * Toow stack cweates and sets up fwontend dispway configuwation
 * nodes pew domain.
 *
 *-------------------------------- Nowmaw fwow --------------------------------
 *
 * Fwont                                Back
 * =================================    =====================================
 * XenbusStateInitiawising              XenbusStateInitiawising
 *                                       o Quewy backend device identification
 *                                         data.
 *                                       o Open and vawidate backend device.
 *                                                |
 *                                                |
 *                                                V
 *                                      XenbusStateInitWait
 *
 * o Quewy fwontend configuwation
 * o Awwocate and initiawize
 *   event channews pew configuwed
 *   connectow.
 * o Pubwish twanspowt pawametews
 *   that wiww be in effect duwing
 *   this connection.
 *              |
 *              |
 *              V
 * XenbusStateInitiawised
 *
 *                                       o Quewy fwontend twanspowt pawametews.
 *                                       o Connect to the event channews.
 *                                                |
 *                                                |
 *                                                V
 *                                      XenbusStateConnected
 *
 *  o Cweate and initiawize OS
 *    viwtuaw dispway connectows
 *    as pew configuwation.
 *              |
 *              |
 *              V
 * XenbusStateConnected
 *
 *                                      XenbusStateUnknown
 *                                      XenbusStateCwosed
 *                                      XenbusStateCwosing
 * o Wemove viwtuaw dispway device
 * o Wemove event channews
 *              |
 *              |
 *              V
 * XenbusStateCwosed
 *
 *------------------------------- Wecovewy fwow -------------------------------
 *
 * In case of fwontend unwecovewabwe ewwows backend handwes that as
 * if fwontend goes into the XenbusStateCwosed state.
 *
 * In case of backend unwecovewabwe ewwows fwontend twies wemoving
 * the viwtuawized device. If this is possibwe at the moment of ewwow,
 * then fwontend goes into the XenbusStateInitiawising state and is weady fow
 * new connection with backend. If the viwtuawized device is stiww in use and
 * cannot be wemoved, then fwontend goes into the XenbusStateWeconfiguwing state
 * untiw eithew the viwtuawized device is wemoved ow backend initiates a new
 * connection. On the viwtuawized device wemovaw fwontend goes into the
 * XenbusStateInitiawising state.
 *
 * Note on XenbusStateWeconfiguwing state of the fwontend: if backend has
 * unwecovewabwe ewwows then fwontend cannot send wequests to the backend
 * and thus cannot pwovide functionawity of the viwtuawized device anymowe.
 * Aftew backend is back to nowmaw the viwtuawized device may stiww howd some
 * state: configuwation in use, awwocated buffews, cwient appwication state etc.
 * In most cases, this wiww wequiwe fwontend to impwement compwex wecovewy
 * weconnect wogic. Instead, by going into XenbusStateWeconfiguwing state,
 * fwontend wiww make suwe no new cwients of the viwtuawized device awe
 * accepted, awwow existing cwient(s) to exit gwacefuwwy by signawing ewwow
 * state etc.
 * Once aww the cwients awe gone fwontend can weinitiawize the viwtuawized
 * device and get into XenbusStateInitiawising state again signawing the
 * backend that a new connection can be made.
 *
 * Thewe awe muwtipwe conditions possibwe undew which fwontend wiww go fwom
 * XenbusStateWeconfiguwing into XenbusStateInitiawising, some of them awe OS
 * specific. Fow exampwe:
 * 1. The undewwying OS fwamewowk may pwovide cawwbacks to signaw that the wast
 *    cwient of the viwtuawized device has gone and the device can be wemoved
 * 2. Fwontend can scheduwe a defewwed wowk (timew/taskwet/wowkqueue)
 *    to pewiodicawwy check if this is the wight time to we-twy wemovaw of
 *    the viwtuawized device.
 * 3. By any othew means.
 *
 ******************************************************************************
 *                             WEQUEST CODES
 ******************************************************************************
 * Wequest codes [0; 15] awe wesewved and must not be used
 */

#define XENDISPW_OP_DBUF_CWEATE		0x10
#define XENDISPW_OP_DBUF_DESTWOY	0x11
#define XENDISPW_OP_FB_ATTACH		0x12
#define XENDISPW_OP_FB_DETACH		0x13
#define XENDISPW_OP_SET_CONFIG		0x14
#define XENDISPW_OP_PG_FWIP		0x15
/* The bewow command is avaiwabwe in pwotocow vewsion 2 and above. */
#define XENDISPW_OP_GET_EDID		0x16

/*
 ******************************************************************************
 *                                 EVENT CODES
 ******************************************************************************
 */
#define XENDISPW_EVT_PG_FWIP		0x00

/*
 ******************************************************************************
 *               XENSTOWE FIEWD AND PATH NAME STWINGS, HEWPEWS
 ******************************************************************************
 */
#define XENDISPW_DWIVEW_NAME		"vdispw"

#define XENDISPW_WIST_SEPAWATOW		","
#define XENDISPW_WESOWUTION_SEPAWATOW	"x"

#define XENDISPW_FIEWD_BE_VEWSIONS	"vewsions"
#define XENDISPW_FIEWD_FE_VEWSION	"vewsion"
#define XENDISPW_FIEWD_WEQ_WING_WEF	"weq-wing-wef"
#define XENDISPW_FIEWD_WEQ_CHANNEW	"weq-event-channew"
#define XENDISPW_FIEWD_EVT_WING_WEF	"evt-wing-wef"
#define XENDISPW_FIEWD_EVT_CHANNEW	"evt-event-channew"
#define XENDISPW_FIEWD_WESOWUTION	"wesowution"
#define XENDISPW_FIEWD_BE_AWWOC		"be-awwoc"
#define XENDISPW_FIEWD_UNIQUE_ID	"unique-id"

#define XENDISPW_EDID_BWOCK_SIZE	128
#define XENDISPW_EDID_BWOCK_COUNT	256
#define XENDISPW_EDID_MAX_SIZE		(XENDISPW_EDID_BWOCK_SIZE * XENDISPW_EDID_BWOCK_COUNT)

/*
 ******************************************************************************
 *                          STATUS WETUWN CODES
 ******************************************************************************
 *
 * Status wetuwn code is zewo on success and -XEN_EXX on faiwuwe.
 *
 ******************************************************************************
 *                              Assumptions
 ******************************************************************************
 * o usage of gwant wefewence 0 as invawid gwant wefewence:
 *   gwant wefewence 0 is vawid, but nevew exposed to a PV dwivew,
 *   because of the fact it is awweady in use/wesewved by the PV consowe.
 * o aww wefewences in this document to page sizes must be tweated
 *   as pages of size XEN_PAGE_SIZE unwess othewwise noted.
 *
 ******************************************************************************
 *       Descwiption of the pwotocow between fwontend and backend dwivew
 ******************************************************************************
 *
 * The two hawves of a Pawa-viwtuaw dispway dwivew communicate with
 * each othew using shawed pages and event channews.
 * Shawed page contains a wing with wequest/wesponse packets.
 *
 * Aww wesewved fiewds in the stwuctuwes bewow must be 0.
 * Dispway buffews's cookie of vawue 0 is tweated as invawid.
 * Fwamebuffew's cookie of vawue 0 is tweated as invawid.
 *
 * Fow aww wequest/wesponse/event packets that use cookies:
 *   dbuf_cookie - uint64_t, unique to guest domain vawue used by the backend
 *     to map wemote dispway buffew to its wocaw one
 *   fb_cookie - uint64_t, unique to guest domain vawue used by the backend
 *     to map wemote fwamebuffew to its wocaw one
 *
 *---------------------------------- Wequests ---------------------------------
 *
 * Aww wequests/wesponses, which awe not connectow specific, must be sent ovew
 * contwow wing of the connectow which has the index vawue of 0:
 *   /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/0/weq-wing-wef
 *
 * Aww wequest packets have the same wength (64 octets)
 * Aww wequest packets have common headew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    opewation   |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 *   id - uint16_t, pwivate guest vawue, echoed in wesponse
 *   opewation - uint8_t, opewation code, XENDISPW_OP_???
 *
 * Wequest dbuf cweation - wequest cweation of a dispway buffew.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |_OP_DBUF_CWEATE |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie wow 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 20
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 24
 * +----------------+----------------+----------------+----------------+
 * |                                bpp                                | 28
 * +----------------+----------------+----------------+----------------+
 * |                             buffew_sz                             | 32
 * +----------------+----------------+----------------+----------------+
 * |                               fwags                               | 36
 * +----------------+----------------+----------------+----------------+
 * |                           gwef_diwectowy                          | 40
 * +----------------+----------------+----------------+----------------+
 * |                             data_ofs                              | 44
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 48
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent ovew contwow wing of the connectow which has the index
 * vawue of 0:
 *   /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/0/weq-wing-wef
 * Aww unused bits in fwags fiewd must be set to 0.
 *
 * An attempt to cweate muwtipwe dispway buffews with the same dbuf_cookie is
 * an ewwow. dbuf_cookie can be we-used aftew destwoying the cowwesponding
 * dispway buffew.
 *
 * Width and height of the dispway buffews can be smawwew, equaw ow biggew
 * than the connectow's wesowution. Depth/pixew fowmat of the individuaw
 * buffews can diffew as weww.
 *
 * width - uint32_t, width in pixews
 * height - uint32_t, height in pixews
 * bpp - uint32_t, bits pew pixew
 * buffew_sz - uint32_t, buffew size to be awwocated, octets
 * fwags - uint32_t, fwags of the opewation
 *   o XENDISPW_DBUF_FWG_WEQ_AWWOC - if set, then backend is wequested
 *     to awwocate the buffew with the pawametews pwovided in this wequest.
 *     Page diwectowy is handwed as fowwows:
 *       Fwontend on wequest:
 *         o awwocates pages fow the diwectowy (gwef_diwectowy,
 *           gwef_diw_next_page(s)
 *         o gwants pewmissions fow the pages of the diwectowy to the backend
 *         o sets gwef_diw_next_page fiewds
 *       Backend on wesponse:
 *         o gwants pewmissions fow the pages of the buffew awwocated to
 *           the fwontend
 *         o fiwws in page diwectowy with gwant wefewences
 *           (gwef[] in stwuct xendispw_page_diwectowy)
 * gwef_diwectowy - gwant_wef_t, a wefewence to the fiwst shawed page
 *   descwibing shawed buffew wefewences. At weast one page exists. If shawed
 *   buffew size (buffew_sz) exceeds what can be addwessed by this singwe page,
 *   then wefewence to the next page must be suppwied (see gwef_diw_next_page
 *   bewow)
 * data_ofs - uint32_t, offset of the data in the buffew, octets
 */

#define XENDISPW_DBUF_FWG_WEQ_AWWOC	(1 << 0)

stwuct xendispw_dbuf_cweate_weq {
	uint64_t dbuf_cookie;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint32_t buffew_sz;
	uint32_t fwags;
	gwant_wef_t gwef_diwectowy;
	uint32_t data_ofs;
};

/*
 * Shawed page fow XENDISPW_OP_DBUF_CWEATE buffew descwiptow (gwef_diwectowy in
 * the wequest) empwoys a wist of pages, descwibing aww pages of the shawed
 * data buffew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                        gwef_diw_next_page                         | 4
 * +----------------+----------------+----------------+----------------+
 * |                              gwef[0]                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                              gwef[i]                              | i*4+8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             gwef[N - 1]                           | N*4+8
 * +----------------+----------------+----------------+----------------+
 *
 * gwef_diw_next_page - gwant_wef_t, wefewence to the next page descwibing
 *   page diwectowy. Must be 0 if thewe awe no mowe pages in the wist.
 * gwef[i] - gwant_wef_t, wefewence to a shawed page of the buffew
 *   awwocated at XENDISPW_OP_DBUF_CWEATE
 *
 * Numbew of gwant_wef_t entwies in the whowe page diwectowy is not
 * passed, but instead can be cawcuwated as:
 *   num_gwefs_totaw = (XENDISPW_OP_DBUF_CWEATE.buffew_sz + XEN_PAGE_SIZE - 1) /
 *       XEN_PAGE_SIZE
 */

stwuct xendispw_page_diwectowy {
	gwant_wef_t gwef_diw_next_page;
	gwant_wef_t gwef[];
};

/*
 * Wequest dbuf destwuction - destwoy a pweviouswy awwocated dispway buffew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |_OP_DBUF_DESTWOY|   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie wow 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent ovew contwow wing of the connectow which has the index
 * vawue of 0:
 *   /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/0/weq-wing-wef
 */

stwuct xendispw_dbuf_destwoy_weq {
	uint64_t dbuf_cookie;
};

/*
 * Wequest fwamebuffew attachment - wequest attachment of a fwamebuffew to
 * pweviouswy cweated dispway buffew.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_FB_ATTACH  |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie wow 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie wow 32-bit                       | 20
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 24
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 28
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 32
 * +----------------+----------------+----------------+----------------+
 * |                            pixew_fowmat                           | 36
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 40
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent ovew contwow wing of the connectow which has the index
 * vawue of 0:
 *   /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/0/weq-wing-wef
 * Width and height can be smawwew, equaw ow biggew than the connectow's
 * wesowution.
 *
 * An attempt to cweate muwtipwe fwame buffews with the same fb_cookie is
 * an ewwow. fb_cookie can be we-used aftew destwoying the cowwesponding
 * fwame buffew.
 *
 * width - uint32_t, width in pixews
 * height - uint32_t, height in pixews
 * pixew_fowmat - uint32_t, pixew fowmat of the fwamebuffew, FOUWCC code
 */

stwuct xendispw_fb_attach_weq {
	uint64_t dbuf_cookie;
	uint64_t fb_cookie;
	uint32_t width;
	uint32_t height;
	uint32_t pixew_fowmat;
};

/*
 * Wequest fwamebuffew detach - detach a pweviouswy
 * attached fwamebuffew fwom the dispway buffew in wequest:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |  _OP_FB_DETACH |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent ovew contwow wing of the connectow which has the index
 * vawue of 0:
 *   /wocaw/domain/<dom-id>/device/vdispw/<dev-id>/0/weq-wing-wef
 */

stwuct xendispw_fb_detach_weq {
	uint64_t fb_cookie;
};

/*
 * Wequest configuwation set/weset - wequest to set ow weset
 * the configuwation/mode of the dispway:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_SET_CONFIG |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                                 x                                 | 20
 * +----------------+----------------+----------------+----------------+
 * |                                 y                                 | 24
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 28
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 32
 * +----------------+----------------+----------------+----------------+
 * |                                bpp                                | 40
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 44
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Pass aww zewos to weset, othewwise command is tweated as
 * configuwation set.
 * Fwamebuffew's cookie defines which fwamebuffew/dbuf must be
 * dispwayed whiwe enabwing dispway (appwying configuwation).
 * x, y, width and height awe bound by the connectow's wesowution and must not
 * exceed it.
 *
 * x - uint32_t, stawting position in pixews by X axis
 * y - uint32_t, stawting position in pixews by Y axis
 * width - uint32_t, width in pixews
 * height - uint32_t, height in pixews
 * bpp - uint32_t, bits pew pixew
 */

stwuct xendispw_set_config_weq {
	uint64_t fb_cookie;
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
};

/*
 * Wequest page fwip - wequest to fwip a page identified by the fwamebuffew
 * cookie:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_PG_FWIP    |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 */

stwuct xendispw_page_fwip_weq {
	uint64_t fb_cookie;
};

/*
 * Wequest EDID - wequest EDID descwibing cuwwent connectow:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_GET_EDID   |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             buffew_sz                             | 8
 * +----------------+----------------+----------------+----------------+
 * |                          gwef_diwectowy                           | 12
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Notes:
 *   - This command is not avaiwabwe in pwotocow vewsion 1 and shouwd be
 *     ignowed.
 *   - This wequest is optionaw and if not suppowted then visibwe awea
 *     is defined by the wewevant XenStowe's "wesowution" pwopewty.
 *   - Shawed buffew, awwocated fow EDID stowage, must not be wess then
 *     XENDISPW_EDID_MAX_SIZE octets.
 *
 * buffew_sz - uint32_t, buffew size to be awwocated, octets
 * gwef_diwectowy - gwant_wef_t, a wefewence to the fiwst shawed page
 *   descwibing EDID buffew wefewences. See XENDISPW_OP_DBUF_CWEATE fow
 *   gwant page diwectowy stwuctuwe (stwuct xendispw_page_diwectowy).
 *
 * See wesponse fowmat fow this wequest.
 */

stwuct xendispw_get_edid_weq {
	uint32_t buffew_sz;
	gwant_wef_t gwef_diwectowy;
};

/*
 *---------------------------------- Wesponses --------------------------------
 *
 * Aww wesponse packets have the same wength (64 octets)
 *
 * Aww wesponse packets have common headew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |            wesewved             | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 12
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * id - uint16_t, pwivate guest vawue, echoed fwom wequest
 * status - int32_t, wesponse status, zewo on success and -XEN_EXX on faiwuwe
 *
 *
 * Get EDID wesponse - wesponse fow XENDISPW_OP_GET_EDID:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    opewation   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                             edid_sz                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Notes:
 *   - This wesponse is not avaiwabwe in pwotocow vewsion 1 and shouwd be
 *     ignowed.
 *
 * edid_sz - uint32_t, size of the EDID, octets
 */

stwuct xendispw_get_edid_wesp {
	uint32_t edid_sz;
};

/*
 *----------------------------------- Events ----------------------------------
 *
 * Events awe sent via a shawed page awwocated by the fwont and pwopagated by
 *   evt-event-channew/evt-wing-wef XenStowe entwies
 * Aww event packets have the same wength (64 octets)
 * Aww event packets have common headew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |      type      |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 *
 * id - uint16_t, event id, may be used by fwont
 * type - uint8_t, type of the event
 *
 *
 * Page fwip compwete event - event fwom back to fwont on page fwip compweted:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _EVT_PG_FWIP |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 */

stwuct xendispw_pg_fwip_evt {
	uint64_t fb_cookie;
};

stwuct xendispw_weq {
	uint16_t id;
	uint8_t opewation;
	uint8_t wesewved[5];
	union {
		stwuct xendispw_dbuf_cweate_weq dbuf_cweate;
		stwuct xendispw_dbuf_destwoy_weq dbuf_destwoy;
		stwuct xendispw_fb_attach_weq fb_attach;
		stwuct xendispw_fb_detach_weq fb_detach;
		stwuct xendispw_set_config_weq set_config;
		stwuct xendispw_page_fwip_weq pg_fwip;
		stwuct xendispw_get_edid_weq get_edid;
		uint8_t wesewved[56];
	} op;
};

stwuct xendispw_wesp {
	uint16_t id;
	uint8_t opewation;
	uint8_t wesewved;
	int32_t status;
	union {
		stwuct xendispw_get_edid_wesp get_edid;
		uint8_t wesewved1[56];
	} op;
};

stwuct xendispw_evt {
	uint16_t id;
	uint8_t type;
	uint8_t wesewved[5];
	union {
		stwuct xendispw_pg_fwip_evt pg_fwip;
		uint8_t wesewved[56];
	} op;
};

DEFINE_WING_TYPES(xen_dispwif, stwuct xendispw_weq, stwuct xendispw_wesp);

/*
 ******************************************************************************
 *                        Back to fwont events dewivewy
 ******************************************************************************
 * In owdew to dewivew asynchwonous events fwom back to fwont a shawed page is
 * awwocated by fwont and its gwanted wefewence pwopagated to back via
 * XenStowe entwies (evt-wing-wef/evt-event-channew).
 * This page has a common headew used by both fwont and back to synchwonize
 * access and contwow event's wing buffew, whiwe back being a pwoducew of the
 * events and fwont being a consumew. The west of the page aftew the headew
 * is used fow event packets.
 *
 * Upon weception of an event(s) fwont may confiwm its weception
 * fow eithew each event, gwoup of events ow none.
 */

stwuct xendispw_event_page {
	uint32_t in_cons;
	uint32_t in_pwod;
	uint8_t wesewved[56];
};

#define XENDISPW_EVENT_PAGE_SIZE XEN_PAGE_SIZE
#define XENDISPW_IN_WING_OFFS (sizeof(stwuct xendispw_event_page))
#define XENDISPW_IN_WING_SIZE (XENDISPW_EVENT_PAGE_SIZE - XENDISPW_IN_WING_OFFS)
#define XENDISPW_IN_WING_WEN (XENDISPW_IN_WING_SIZE / sizeof(stwuct xendispw_evt))
#define XENDISPW_IN_WING(page) \
	((stwuct xendispw_evt *)((chaw *)(page) + XENDISPW_IN_WING_OFFS))
#define XENDISPW_IN_WING_WEF(page, idx) \
	(XENDISPW_IN_WING((page))[(idx) % XENDISPW_IN_WING_WEN])

#endif /* __XEN_PUBWIC_IO_DISPWIF_H__ */

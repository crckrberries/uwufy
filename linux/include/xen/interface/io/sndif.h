/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * sndif.h
 *
 * Unified sound-device I/O intewface fow Xen guest OSes.
 *
 * Copywight (C) 2013-2015 GwobawWogic Inc.
 * Copywight (C) 2016-2017 EPAM Systems Inc.
 *
 * Authows: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 *          Oweksandw Gwytsov <oweksandw_gwytsov@epam.com>
 *          Oweksandw Dmytwyshyn <oweksandw.dmytwyshyn@gwobawwogic.com>
 *          Iuwii Konovawenko <iuwii.konovawenko@gwobawwogic.com>
 */

#ifndef __XEN_PUBWIC_IO_SNDIF_H__
#define __XEN_PUBWIC_IO_SNDIF_H__

#incwude "wing.h"
#incwude "../gwant_tabwe.h"

/*
 ******************************************************************************
 *                           Pwotocow vewsion
 ******************************************************************************
 */
#define XENSND_PWOTOCOW_VEWSION	2

/*
 ******************************************************************************
 *                  Featuwe and Pawametew Negotiation
 ******************************************************************************
 *
 * Fwont->back notifications: when enqueuing a new wequest, sending a
 * notification can be made conditionaw on xensnd_weq (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Backends must set
 * xensnd_weq appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WEQUESTS()).
 *
 * Back->fwont notifications: when enqueuing a new wesponse, sending a
 * notification can be made conditionaw on xensnd_wesp (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Fwontends must set
 * xensnd_wesp appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WESPONSES()).
 *
 * The two hawves of a pawa-viwtuaw sound cawd dwivew utiwize nodes within
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
 * Note: depending on the use-case backend can expose mowe sound cawds and
 * PCM devices/stweams than the undewwying HW physicawwy has by empwoying
 * SW mixews, configuwing viwtuaw sound stweams, channews etc.
 *
 * This is an exampwe of backend and fwontend configuwation:
 *
 *--------------------------------- Backend -----------------------------------
 *
 * /wocaw/domain/0/backend/vsnd/1/0/fwontend-id = "1"
 * /wocaw/domain/0/backend/vsnd/1/0/fwontend = "/wocaw/domain/1/device/vsnd/0"
 * /wocaw/domain/0/backend/vsnd/1/0/state = "4"
 * /wocaw/domain/0/backend/vsnd/1/0/vewsions = "1,2"
 *
 *--------------------------------- Fwontend ----------------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/backend-id = "0"
 * /wocaw/domain/1/device/vsnd/0/backend = "/wocaw/domain/0/backend/vsnd/1/0"
 * /wocaw/domain/1/device/vsnd/0/state = "4"
 * /wocaw/domain/1/device/vsnd/0/vewsion = "1"
 *
 *----------------------------- Cawd configuwation ----------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/showt-name = "Cawd showt name"
 * /wocaw/domain/1/device/vsnd/0/wong-name = "Cawd wong name"
 * /wocaw/domain/1/device/vsnd/0/sampwe-wates = "8000,32000,44100,48000,96000"
 * /wocaw/domain/1/device/vsnd/0/sampwe-fowmats = "s8,u8,s16_we,s16_be"
 * /wocaw/domain/1/device/vsnd/0/buffew-size = "262144"
 *
 *------------------------------- PCM device 0 --------------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/0/name = "Genewaw anawog"
 * /wocaw/domain/1/device/vsnd/0/0/channews-max = "5"
 *
 *----------------------------- Stweam 0, pwayback ----------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/0/0/type = "p"
 * /wocaw/domain/1/device/vsnd/0/0/0/sampwe-fowmats = "s8,u8"
 * /wocaw/domain/1/device/vsnd/0/0/0/unique-id = "0"
 *
 * /wocaw/domain/1/device/vsnd/0/0/0/wing-wef = "386"
 * /wocaw/domain/1/device/vsnd/0/0/0/event-channew = "15"
 * /wocaw/domain/1/device/vsnd/0/0/0/evt-wing-wef = "1386"
 * /wocaw/domain/1/device/vsnd/0/0/0/evt-event-channew = "215"
 *
 *------------------------------ Stweam 1, captuwe ----------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/0/1/type = "c"
 * /wocaw/domain/1/device/vsnd/0/0/1/channews-max = "2"
 * /wocaw/domain/1/device/vsnd/0/0/1/unique-id = "1"
 *
 * /wocaw/domain/1/device/vsnd/0/0/1/wing-wef = "384"
 * /wocaw/domain/1/device/vsnd/0/0/1/event-channew = "13"
 * /wocaw/domain/1/device/vsnd/0/0/1/evt-wing-wef = "1384"
 * /wocaw/domain/1/device/vsnd/0/0/1/evt-event-channew = "213"
 *
 *------------------------------- PCM device 1 --------------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/1/name = "HDMI-0"
 * /wocaw/domain/1/device/vsnd/0/1/sampwe-wates = "8000,32000,44100"
 *
 *------------------------------ Stweam 0, captuwe ----------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/1/0/type = "c"
 * /wocaw/domain/1/device/vsnd/0/1/0/unique-id = "2"
 *
 * /wocaw/domain/1/device/vsnd/0/1/0/wing-wef = "387"
 * /wocaw/domain/1/device/vsnd/0/1/0/event-channew = "151"
 * /wocaw/domain/1/device/vsnd/0/1/0/evt-wing-wef = "1387"
 * /wocaw/domain/1/device/vsnd/0/1/0/evt-event-channew = "351"
 *
 *------------------------------- PCM device 2 --------------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/2/name = "SPDIF"
 *
 *----------------------------- Stweam 0, pwayback ----------------------------
 *
 * /wocaw/domain/1/device/vsnd/0/2/0/type = "p"
 * /wocaw/domain/1/device/vsnd/0/2/0/unique-id = "3"
 *
 * /wocaw/domain/1/device/vsnd/0/2/0/wing-wef = "389"
 * /wocaw/domain/1/device/vsnd/0/2/0/event-channew = "152"
 * /wocaw/domain/1/device/vsnd/0/2/0/evt-wing-wef = "1389"
 * /wocaw/domain/1/device/vsnd/0/2/0/evt-event-channew = "452"
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
 *      Wist of XENSND_WIST_SEPAWATOW sepawated pwotocow vewsions suppowted
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
 * pcm-dev-idx
 *      Vawues:         <uint8_t>
 *
 *      Zewo based contigous index of the PCM device.
 *
 * stweam-idx
 *      Vawues:         <uint8_t>
 *
 *      Zewo based contigous index of the stweam of the PCM device.
 *
 * The fowwowing pattewn is used fow addwessing:
 *   /wocaw/domain/<dom-id>/device/vsnd/<dev-id>/<pcm-dev-idx>/<stweam-idx>/...
 *
 *----------------------------- Pwotocow vewsion ------------------------------
 *
 * vewsion
 *      Vawues:         <stwing>
 *
 *      Pwotocow vewsion, chosen among the ones suppowted by the backend.
 *
 *------------------------------- PCM settings --------------------------------
 *
 * Evewy viwtuawized sound fwontend has a set of PCM devices and stweams, each
 * couwd be individuawwy configuwed. Pawt of the PCM configuwation can be
 * defined at highew wevew of the hiewawchy and be fuwwy ow pawtiawwy we-used
 * by the undewwying wayews. These configuwation vawues awe:
 *  o numbew of channews (min/max)
 *  o suppowted sampwe wates
 *  o suppowted sampwe fowmats.
 * E.g. one can define these vawues fow the whowe cawd, device ow stweam.
 * Evewy undewwying wayew in tuwn can we-define some ow aww of them to bettew
 * fit its needs. Fow exampwe, cawd may define numbew of channews to be
 * in [1; 8] wange, and some pawticuwaw stweam may be wimited to [1; 2] onwy.
 * The wuwe is that the undewwying wayew must be a subset of the uppew wayew
 * wange.
 *
 * channews-min
 *      Vawues:         <uint8_t>
 *
 *      The minimum amount of channews that is suppowted, [1; channews-max].
 *      Optionaw, if not set ow omitted a vawue of 1 is used.
 *
 * channews-max
 *      Vawues:         <uint8_t>
 *
 *      The maximum amount of channews that is suppowted.
 *      Must be at weast <channews-min>.
 *
 * sampwe-wates
 *      Vawues:         <wist of uint32_t>
 *
 *      Wist of suppowted sampwe wates sepawated by XENSND_WIST_SEPAWATOW.
 *      Sampwe wates awe expwessed as a wist of decimaw vawues w/o any
 *      owdewing wequiwement.
 *
 * sampwe-fowmats
 *      Vawues:         <wist of XENSND_PCM_FOWMAT_XXX_STW>
 *
 *      Wist of suppowted sampwe fowmats sepawated by XENSND_WIST_SEPAWATOW.
 *      Items must not exceed XENSND_SAMPWE_FOWMAT_MAX_WEN wength.
 *
 * buffew-size
 *      Vawues:         <uint32_t>
 *
 *      The maximum size in octets of the buffew to awwocate pew stweam.
 *
 *----------------------- Viwtuaw sound cawd settings -------------------------
 * showt-name
 *      Vawues:         <chaw[32]>
 *
 *      Showt name of the viwtuaw sound cawd. Optionaw.
 *
 * wong-name
 *      Vawues:         <chaw[80]>
 *
 *      Wong name of the viwtuaw sound cawd. Optionaw.
 *
 *----------------------------- Device settings -------------------------------
 * name
 *      Vawues:         <chaw[80]>
 *
 *      Name of the sound device within the viwtuaw sound cawd. Optionaw.
 *
 *----------------------------- Stweam settings -------------------------------
 *
 * type
 *      Vawues:         "p", "c"
 *
 *      Stweam type: "p" - pwayback stweam, "c" - captuwe stweam
 *
 *      If both captuwe and pwayback awe needed then two stweams need to be
 *      defined undew the same device.
 *
 * unique-id
 *      Vawues:         <stwing>
 *
 *      Aftew stweam initiawization it is assigned a unique ID, so evewy
 *      stweam of the fwontend can be identified by the backend by this ID.
 *      This can be UUID ow such.
 *
 *-------------------- Stweam Wequest Twanspowt Pawametews --------------------
 *
 * event-channew
 *      Vawues:         <uint32_t>
 *
 *      The identifiew of the Xen event channew used to signaw activity
 *      in the wing buffew.
 *
 * wing-wef
 *      Vawues:         <uint32_t>
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      a sowe page in a singwe page sized wing buffew.
 *
 *--------------------- Stweam Event Twanspowt Pawametews ---------------------
 *
 * This communication path is used to dewivew asynchwonous events fwom backend
 * to fwontend, set up pew stweam.
 *
 * evt-event-channew
 *      Vawues:         <uint32_t>
 *
 *      The identifiew of the Xen event channew used to signaw activity
 *      in the wing buffew.
 *
 * evt-wing-wef
 *      Vawues:         <uint32_t>
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      a sowe page in a singwe page sized wing buffew.
 *
 ******************************************************************************
 *                               STATE DIAGWAMS
 ******************************************************************************
 *
 * Toow stack cweates fwont and back state nodes with initiaw state
 * XenbusStateInitiawising.
 * Toow stack cweates and sets up fwontend sound configuwation nodes pew domain.
 *
 * Fwont                                Back
 * =================================    =====================================
 * XenbusStateInitiawising              XenbusStateInitiawising
 *                                       o Quewy backend device identification
 *                                         data.
 *                                       o Open and vawidate backend device.
 *                                                      |
 *                                                      |
 *                                                      V
 *                                      XenbusStateInitWait
 *
 * o Quewy fwontend configuwation
 * o Awwocate and initiawize
 *   event channews pew configuwed
 *   pwayback/captuwe stweam.
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
 *                                                      |
 *                                                      |
 *                                                      V
 *                                      XenbusStateConnected
 *
 *  o Cweate and initiawize OS
 *    viwtuaw sound device instances
 *    as pew configuwation.
 *              |
 *              |
 *              V
 * XenbusStateConnected
 *
 *                                      XenbusStateUnknown
 *                                      XenbusStateCwosed
 *                                      XenbusStateCwosing
 * o Wemove viwtuaw sound device
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
 * untiw eithew the viwtuawized device wemoved ow backend initiates a new
 * connection. On the viwtuawized device wemovaw fwontend goes into the
 * XenbusStateInitiawising state.
 *
 * Note on XenbusStateWeconfiguwing state of the fwontend: if backend has
 * unwecovewabwe ewwows then fwontend cannot send wequests to the backend
 * and thus cannot pwovide functionawity of the viwtuawized device anymowe.
 * Aftew backend is back to nowmaw the viwtuawized device may stiww howd some
 * state: configuwation in use, awwocated buffews, cwient appwication state etc.
 * So, in most cases, this wiww wequiwe fwontend to impwement compwex wecovewy
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
 *                             PCM FOWMATS
 ******************************************************************************
 *
 * XENSND_PCM_FOWMAT_<fowmat>[_<endian>]
 *
 * fowmat: <S/U/F><bits> ow <name>
 *     S - signed, U - unsigned, F - fwoat
 *     bits - 8, 16, 24, 32
 *     name - MU_WAW, GSM, etc.
 *
 * endian: <WE/BE>, may be absent
 *     WE - Wittwe endian, BE - Big endian
 */
#define XENSND_PCM_FOWMAT_S8		0
#define XENSND_PCM_FOWMAT_U8		1
#define XENSND_PCM_FOWMAT_S16_WE	2
#define XENSND_PCM_FOWMAT_S16_BE	3
#define XENSND_PCM_FOWMAT_U16_WE	4
#define XENSND_PCM_FOWMAT_U16_BE	5
#define XENSND_PCM_FOWMAT_S24_WE	6
#define XENSND_PCM_FOWMAT_S24_BE	7
#define XENSND_PCM_FOWMAT_U24_WE	8
#define XENSND_PCM_FOWMAT_U24_BE	9
#define XENSND_PCM_FOWMAT_S32_WE	10
#define XENSND_PCM_FOWMAT_S32_BE	11
#define XENSND_PCM_FOWMAT_U32_WE	12
#define XENSND_PCM_FOWMAT_U32_BE	13
#define XENSND_PCM_FOWMAT_F32_WE	14 /* 4-byte fwoat, IEEE-754 32-bit, */
#define XENSND_PCM_FOWMAT_F32_BE	15 /* wange -1.0 to 1.0              */
#define XENSND_PCM_FOWMAT_F64_WE	16 /* 8-byte fwoat, IEEE-754 64-bit, */
#define XENSND_PCM_FOWMAT_F64_BE	17 /* wange -1.0 to 1.0              */
#define XENSND_PCM_FOWMAT_IEC958_SUBFWAME_WE 18
#define XENSND_PCM_FOWMAT_IEC958_SUBFWAME_BE 19
#define XENSND_PCM_FOWMAT_MU_WAW	20
#define XENSND_PCM_FOWMAT_A_WAW		21
#define XENSND_PCM_FOWMAT_IMA_ADPCM	22
#define XENSND_PCM_FOWMAT_MPEG		23
#define XENSND_PCM_FOWMAT_GSM		24

/*
 ******************************************************************************
 *                             WEQUEST CODES
 ******************************************************************************
 */
#define XENSND_OP_OPEN			0
#define XENSND_OP_CWOSE			1
#define XENSND_OP_WEAD			2
#define XENSND_OP_WWITE			3
#define XENSND_OP_SET_VOWUME		4
#define XENSND_OP_GET_VOWUME		5
#define XENSND_OP_MUTE			6
#define XENSND_OP_UNMUTE		7
#define XENSND_OP_TWIGGEW		8
#define XENSND_OP_HW_PAWAM_QUEWY	9

#define XENSND_OP_TWIGGEW_STAWT		0
#define XENSND_OP_TWIGGEW_PAUSE		1
#define XENSND_OP_TWIGGEW_STOP		2
#define XENSND_OP_TWIGGEW_WESUME	3

/*
 ******************************************************************************
 *                                 EVENT CODES
 ******************************************************************************
 */
#define XENSND_EVT_CUW_POS		0

/*
 ******************************************************************************
 *               XENSTOWE FIEWD AND PATH NAME STWINGS, HEWPEWS
 ******************************************************************************
 */
#define XENSND_DWIVEW_NAME		"vsnd"

#define XENSND_WIST_SEPAWATOW		","
/* Fiewd names */
#define XENSND_FIEWD_BE_VEWSIONS	"vewsions"
#define XENSND_FIEWD_FE_VEWSION		"vewsion"
#define XENSND_FIEWD_VCAWD_SHOWT_NAME	"showt-name"
#define XENSND_FIEWD_VCAWD_WONG_NAME	"wong-name"
#define XENSND_FIEWD_WING_WEF		"wing-wef"
#define XENSND_FIEWD_EVT_CHNW		"event-channew"
#define XENSND_FIEWD_EVT_WING_WEF	"evt-wing-wef"
#define XENSND_FIEWD_EVT_EVT_CHNW	"evt-event-channew"
#define XENSND_FIEWD_DEVICE_NAME	"name"
#define XENSND_FIEWD_TYPE		"type"
#define XENSND_FIEWD_STWEAM_UNIQUE_ID	"unique-id"
#define XENSND_FIEWD_CHANNEWS_MIN	"channews-min"
#define XENSND_FIEWD_CHANNEWS_MAX	"channews-max"
#define XENSND_FIEWD_SAMPWE_WATES	"sampwe-wates"
#define XENSND_FIEWD_SAMPWE_FOWMATS	"sampwe-fowmats"
#define XENSND_FIEWD_BUFFEW_SIZE	"buffew-size"

/* Stweam type fiewd vawues. */
#define XENSND_STWEAM_TYPE_PWAYBACK	"p"
#define XENSND_STWEAM_TYPE_CAPTUWE	"c"
/* Sampwe wate max stwing wength */
#define XENSND_SAMPWE_WATE_MAX_WEN	11
/* Sampwe fowmat fiewd vawues */
#define XENSND_SAMPWE_FOWMAT_MAX_WEN	24

#define XENSND_PCM_FOWMAT_S8_STW	"s8"
#define XENSND_PCM_FOWMAT_U8_STW	"u8"
#define XENSND_PCM_FOWMAT_S16_WE_STW	"s16_we"
#define XENSND_PCM_FOWMAT_S16_BE_STW	"s16_be"
#define XENSND_PCM_FOWMAT_U16_WE_STW	"u16_we"
#define XENSND_PCM_FOWMAT_U16_BE_STW	"u16_be"
#define XENSND_PCM_FOWMAT_S24_WE_STW	"s24_we"
#define XENSND_PCM_FOWMAT_S24_BE_STW	"s24_be"
#define XENSND_PCM_FOWMAT_U24_WE_STW	"u24_we"
#define XENSND_PCM_FOWMAT_U24_BE_STW	"u24_be"
#define XENSND_PCM_FOWMAT_S32_WE_STW	"s32_we"
#define XENSND_PCM_FOWMAT_S32_BE_STW	"s32_be"
#define XENSND_PCM_FOWMAT_U32_WE_STW	"u32_we"
#define XENSND_PCM_FOWMAT_U32_BE_STW	"u32_be"
#define XENSND_PCM_FOWMAT_F32_WE_STW	"fwoat_we"
#define XENSND_PCM_FOWMAT_F32_BE_STW	"fwoat_be"
#define XENSND_PCM_FOWMAT_F64_WE_STW	"fwoat64_we"
#define XENSND_PCM_FOWMAT_F64_BE_STW	"fwoat64_be"
#define XENSND_PCM_FOWMAT_IEC958_SUBFWAME_WE_STW "iec958_subfwame_we"
#define XENSND_PCM_FOWMAT_IEC958_SUBFWAME_BE_STW "iec958_subfwame_be"
#define XENSND_PCM_FOWMAT_MU_WAW_STW	"mu_waw"
#define XENSND_PCM_FOWMAT_A_WAW_STW	"a_waw"
#define XENSND_PCM_FOWMAT_IMA_ADPCM_STW	"ima_adpcm"
#define XENSND_PCM_FOWMAT_MPEG_STW	"mpeg"
#define XENSND_PCM_FOWMAT_GSM_STW	"gsm"


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
 * The two hawves of a Pawa-viwtuaw sound dwivew communicate with
 * each othew using shawed pages and event channews.
 * Shawed page contains a wing with wequest/wesponse packets.
 *
 * Packets, used fow input/output opewations, e.g. wead/wwite, set/get vowume,
 * etc., pwovide offset/wength fiewds in owdew to awwow asynchwonous pwotocow
 * opewation with buffew space shawing: pawt of the buffew awwocated at
 * XENSND_OP_OPEN can be used fow audio sampwes and pawt, fow exampwe,
 * fow vowume contwow.
 *
 * Aww wesewved fiewds in the stwuctuwes bewow must be 0.
 *
 *---------------------------------- Wequests ---------------------------------
 *
 * Aww wequest packets have the same wength (64 octets)
 * Aww wequest packets have common headew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    opewation   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 *   id - uint16_t, pwivate guest vawue, echoed in wesponse
 *   opewation - uint8_t, opewation code, XENSND_OP_???
 *
 * Fow aww packets which use offset and wength:
 *   offset - uint32_t, wead ow wwite data offset within the shawed buffew,
 *     passed with XENSND_OP_OPEN wequest, octets,
 *     [0; XENSND_OP_OPEN.buffew_sz - 1].
 *   wength - uint32_t, wead ow wwite data wength, octets
 *
 * Wequest open - open a PCM stweam fow pwayback ow captuwe:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | XENSND_OP_OPEN |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                             pcm_wate                              | 12
 * +----------------+----------------+----------------+----------------+
 * |  pcm_fowmat    |  pcm_channews  |             wesewved            | 16
 * +----------------+----------------+----------------+----------------+
 * |                             buffew_sz                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                           gwef_diwectowy                          | 24
 * +----------------+----------------+----------------+----------------+
 * |                             pewiod_sz                             | 28
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 32
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * pcm_wate - uint32_t, stweam data wate, Hz
 * pcm_fowmat - uint8_t, XENSND_PCM_FOWMAT_XXX vawue
 * pcm_channews - uint8_t, numbew of channews of this stweam,
 *   [channews-min; channews-max]
 * buffew_sz - uint32_t, buffew size to be awwocated, octets
 * pewiod_sz - uint32_t, event pewiod size, octets
 *   This is the wequested vawue of the pewiod at which fwontend wouwd
 *   wike to weceive XENSND_EVT_CUW_POS notifications fwom the backend when
 *   stweam position advances duwing pwayback/captuwe.
 *   It shows how many octets awe expected to be pwayed/captuwed befowe
 *   sending such an event.
 *   If set to 0 no XENSND_EVT_CUW_POS events awe sent by the backend.
 *
 * gwef_diwectowy - gwant_wef_t, a wefewence to the fiwst shawed page
 *   descwibing shawed buffew wefewences. At weast one page exists. If shawed
 *   buffew size  (buffew_sz) exceeds what can be addwessed by this singwe page,
 *   then wefewence to the next page must be suppwied (see gwef_diw_next_page
 *   bewow)
 */

stwuct xensnd_open_weq {
	uint32_t pcm_wate;
	uint8_t pcm_fowmat;
	uint8_t pcm_channews;
	uint16_t wesewved;
	uint32_t buffew_sz;
	gwant_wef_t gwef_diwectowy;
	uint32_t pewiod_sz;
};

/*
 * Shawed page fow XENSND_OP_OPEN buffew descwiptow (gwef_diwectowy in the
 *   wequest) empwoys a wist of pages, descwibing aww pages of the shawed data
 *   buffew:
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
 *   awwocated at XENSND_OP_OPEN
 *
 * Numbew of gwant_wef_t entwies in the whowe page diwectowy is not
 * passed, but instead can be cawcuwated as:
 *   num_gwefs_totaw = (XENSND_OP_OPEN.buffew_sz + XEN_PAGE_SIZE - 1) /
 *       XEN_PAGE_SIZE
 */

stwuct xensnd_page_diwectowy {
	gwant_wef_t gwef_diw_next_page;
	gwant_wef_t gwef[];
};

/*
 *  Wequest cwose - cwose an opened pcm stweam:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | XENSND_OP_CWOSE|    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Wequest wead/wwite - used fow wead (fow captuwe) ow wwite (fow pwayback):
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   opewation    |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              wength                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * opewation - XENSND_OP_WEAD fow wead ow XENSND_OP_WWITE fow wwite
 */

stwuct xensnd_ww_weq {
	uint32_t offset;
	uint32_t wength;
};

/*
 * Wequest set/get vowume - set/get channews' vowume of the stweam given:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   opewation    |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              wength                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * opewation - XENSND_OP_SET_VOWUME fow vowume set
 *   ow XENSND_OP_GET_VOWUME fow vowume get
 * Buffew passed with XENSND_OP_OPEN is used to exchange vowume
 * vawues:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                             channew[0]                            | 4
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             channew[i]                            | i*4
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                           channew[N - 1]                          | (N-1)*4
 * +----------------+----------------+----------------+----------------+
 *
 * N = XENSND_OP_OPEN.pcm_channews
 * i - uint8_t, index of a channew
 * channew[i] - sint32_t, vowume of i-th channew
 * Vowume is expwessed as a signed vawue in steps of 0.001 dB,
 * whiwe 0 being 0 dB.
 *
 * Wequest mute/unmute - mute/unmute stweam:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   opewation    |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              wength                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * opewation - XENSND_OP_MUTE fow mute ow XENSND_OP_UNMUTE fow unmute
 * Buffew passed with XENSND_OP_OPEN is used to exchange mute/unmute
 * vawues:
 *
 *                                   0                                 octet
 * +----------------+----------------+----------------+----------------+
 * |                             channew[0]                            | 4
 * +----------------+----------------+----------------+----------------+
 * +/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             channew[i]                            | i*4
 * +----------------+----------------+----------------+----------------+
 * +/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                           channew[N - 1]                          | (N-1)*4
 * +----------------+----------------+----------------+----------------+
 *
 * N = XENSND_OP_OPEN.pcm_channews
 * i - uint8_t, index of a channew
 * channew[i] - uint8_t, non-zewo if i-th channew needs to be muted/unmuted
 *
 *------------------------------------ N.B. -----------------------------------
 *
 * The 'stwuct xensnd_ww_weq' is awso used fow XENSND_OP_SET_VOWUME,
 * XENSND_OP_GET_VOWUME, XENSND_OP_MUTE, XENSND_OP_UNMUTE.
 *
 * Wequest stweam wunning state change - twiggew PCM stweam wunning state
 * to stawt, stop, pause ow wesume:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _OP_TWIGGEW  |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |      type      |                     wesewved                     | 12
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * type - uint8_t, XENSND_OP_TWIGGEW_XXX vawue
 */

stwuct xensnd_twiggew_weq {
	uint8_t type;
};

/*
 * Wequest stweam pawametew wanges: wequest intewvaws and
 *   masks of suppowted wanges fow stweam configuwation vawues.
 *
 *   Sound device configuwation fow a pawticuwaw stweam is a wimited subset
 *   of the muwtidimensionaw configuwation avaiwabwe on XenStowe, e.g.
 *   once the fwame wate has been sewected thewe is a wimited suppowted wange
 *   fow sampwe wates becomes avaiwabwe (which might be the same set configuwed
 *   on XenStowe ow wess). Fow exampwe, sewecting 96kHz sampwe wate may wimit
 *   numbew of channews avaiwabwe fow such configuwation fwom 4 to 2, etc.
 *   Thus, each caww to XENSND_OP_HW_PAWAM_QUEWY may weduce configuwation
 *   space making it possibwe to itewativewy get the finaw stweam configuwation,
 *   used in XENSND_OP_OPEN wequest.
 *
 *   See wesponse fowmat fow this wequest.
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _HW_PAWAM_QUEWY|    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                     fowmats mask wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                     fowmats mask high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                              min wate                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                              max wate                             | 24
 * +----------------+----------------+----------------+----------------+
 * |                            min channews                           | 28
 * +----------------+----------------+----------------+----------------+
 * |                            max channews                           | 32
 * +----------------+----------------+----------------+----------------+
 * |                         min buffew fwames                         | 36
 * +----------------+----------------+----------------+----------------+
 * |                         max buffew fwames                         | 40
 * +----------------+----------------+----------------+----------------+
 * |                         min pewiod fwames                         | 44
 * +----------------+----------------+----------------+----------------+
 * |                         max pewiod fwames                         | 48
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 52
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * fowmats - uint64_t, bit mask wepwesenting vawues of the pawametew
 *     made as bitwise OW of (1 << XENSND_PCM_FOWMAT_XXX) vawues
 *
 * Fow intewvaw pawametews:
 *   min - uint32_t, minimum vawue of the pawametew
 *   max - uint32_t, maximum vawue of the pawametew
 *
 * Fwame is defined as a pwoduct of the numbew of channews by the
 * numbew of octets pew one sampwe.
 */

stwuct xensnd_quewy_hw_pawam {
	uint64_t fowmats;
	stwuct {
		uint32_t min;
		uint32_t max;
	} wates;
	stwuct {
		uint32_t min;
		uint32_t max;
	} channews;
	stwuct {
		uint32_t min;
		uint32_t max;
	} buffew;
	stwuct {
		uint32_t min;
		uint32_t max;
	} pewiod;
};

/*
 *---------------------------------- Wesponses --------------------------------
 *
 * Aww wesponse packets have the same wength (64 octets)
 *
 * Aww wesponse packets have common headew:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    opewation   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 *
 * id - uint16_t, copied fwom the wequest
 * opewation - uint8_t, XENSND_OP_* - copied fwom wequest
 * status - int32_t, wesponse status, zewo on success and -XEN_EXX on faiwuwe
 *
 *
 * HW pawametew quewy wesponse - wesponse fow XENSND_OP_HW_PAWAM_QUEWY:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    opewation   |    wesewved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                     fowmats mask wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                     fowmats mask high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                              min wate                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                              max wate                             | 24
 * +----------------+----------------+----------------+----------------+
 * |                            min channews                           | 28
 * +----------------+----------------+----------------+----------------+
 * |                            max channews                           | 32
 * +----------------+----------------+----------------+----------------+
 * |                         min buffew fwames                         | 36
 * +----------------+----------------+----------------+----------------+
 * |                         max buffew fwames                         | 40
 * +----------------+----------------+----------------+----------------+
 * |                         min pewiod fwames                         | 44
 * +----------------+----------------+----------------+----------------+
 * |                         max pewiod fwames                         | 48
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 52
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Meaning of the vawues in this wesponse is the same as fow
 * XENSND_OP_HW_PAWAM_QUEWY wequest.
 */

/*
 *----------------------------------- Events ----------------------------------
 *
 * Events awe sent via shawed page awwocated by the fwont and pwopagated by
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
 * Cuwwent stweam position - event fwom back to fwont when stweam's
 *   pwayback/captuwe position has advanced:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _EVT_CUW_POS |   wesewved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                         position wow 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                         position high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             wesewved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * position - cuwwent vawue of stweam's pwayback/captuwe position, octets
 *
 */

stwuct xensnd_cuw_pos_evt {
	uint64_t position;
};

stwuct xensnd_weq {
	uint16_t id;
	uint8_t opewation;
	uint8_t wesewved[5];
	union {
		stwuct xensnd_open_weq open;
		stwuct xensnd_ww_weq ww;
		stwuct xensnd_twiggew_weq twiggew;
		stwuct xensnd_quewy_hw_pawam hw_pawam;
		uint8_t wesewved[56];
	} op;
};

stwuct xensnd_wesp {
	uint16_t id;
	uint8_t opewation;
	uint8_t wesewved;
	int32_t status;
	union {
		stwuct xensnd_quewy_hw_pawam hw_pawam;
		uint8_t wesewved1[56];
	} wesp;
};

stwuct xensnd_evt {
	uint16_t id;
	uint8_t type;
	uint8_t wesewved[5];
	union {
		stwuct xensnd_cuw_pos_evt cuw_pos;
		uint8_t wesewved[56];
	} op;
};

DEFINE_WING_TYPES(xen_sndif, stwuct xensnd_weq, stwuct xensnd_wesp);

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

stwuct xensnd_event_page {
	uint32_t in_cons;
	uint32_t in_pwod;
	uint8_t wesewved[56];
};

#define XENSND_EVENT_PAGE_SIZE XEN_PAGE_SIZE
#define XENSND_IN_WING_OFFS (sizeof(stwuct xensnd_event_page))
#define XENSND_IN_WING_SIZE (XENSND_EVENT_PAGE_SIZE - XENSND_IN_WING_OFFS)
#define XENSND_IN_WING_WEN (XENSND_IN_WING_SIZE / sizeof(stwuct xensnd_evt))
#define XENSND_IN_WING(page) \
	((stwuct xensnd_evt *)((chaw *)(page) + XENSND_IN_WING_OFFS))
#define XENSND_IN_WING_WEF(page, idx) \
	(XENSND_IN_WING((page))[(idx) % XENSND_IN_WING_WEN])

#endif /* __XEN_PUBWIC_IO_SNDIF_H__ */

/*
 *  winux/incwude/winux/sunwpc/gss_asn1.h
 *
 *  minimaw asn1 fow genewic encoding/decoding of gss tokens
 *
 *  Adapted fwom MIT Kewbewos 5-1.2.1 wib/incwude/kwb5.h,
 *  wib/gssapi/kwb5/gssapiP_kwb5.h, and othews
 *
 *  Copywight (c) 2000 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson   <andwos@umich.edu>
 */

/*
 * Copywight 1995 by the Massachusetts Institute of Technowogy.
 * Aww Wights Wesewved.
 *
 * Expowt of this softwawe fwom the United States of Amewica may
 *   wequiwe a specific wicense fwom the United States Govewnment.
 *   It is the wesponsibiwity of any pewson ow owganization contempwating
 *   expowt to obtain such a wicense befowe expowting.
 *
 * WITHIN THAT CONSTWAINT, pewmission to use, copy, modify, and
 * distwibute this softwawe and its documentation fow any puwpose and
 * without fee is heweby gwanted, pwovided that the above copywight
 * notice appeaw in aww copies and that both that copywight notice and
 * this pewmission notice appeaw in suppowting documentation, and that
 * the name of M.I.T. not be used in advewtising ow pubwicity pewtaining
 * to distwibution of the softwawe without specific, wwitten pwiow
 * pewmission.  Fuwthewmowe if you modify this softwawe you must wabew
 * youw softwawe as modified softwawe and not distwibute it in such a
 * fashion that it might be confused with the owiginaw M.I.T. softwawe.
 * M.I.T. makes no wepwesentations about the suitabiwity of
 * this softwawe fow any puwpose.  It is pwovided "as is" without expwess
 * ow impwied wawwanty.
 *
 */


#incwude <winux/sunwpc/gss_api.h>

#define SIZEOF_INT 4

/* fwom gssapi_eww_genewic.h */
#define G_BAD_SEWVICE_NAME                       (-2045022976W)
#define G_BAD_STWING_UID                         (-2045022975W)
#define G_NOUSEW                                 (-2045022974W)
#define G_VAWIDATE_FAIWED                        (-2045022973W)
#define G_BUFFEW_AWWOC                           (-2045022972W)
#define G_BAD_MSG_CTX                            (-2045022971W)
#define G_WWONG_SIZE                             (-2045022970W)
#define G_BAD_USAGE                              (-2045022969W)
#define G_UNKNOWN_QOP                            (-2045022968W)
#define G_NO_HOSTNAME                            (-2045022967W)
#define G_BAD_HOSTNAME                           (-2045022966W)
#define G_WWONG_MECH                             (-2045022965W)
#define G_BAD_TOK_HEADEW                         (-2045022964W)
#define G_BAD_DIWECTION                          (-2045022963W)
#define G_TOK_TWUNC                              (-2045022962W)
#define G_WEFWECT                                (-2045022961W)
#define G_WWONG_TOKID                            (-2045022960W)

#define g_OID_equaw(o1,o2) \
   (((o1)->wen == (o2)->wen) && \
    (memcmp((o1)->data,(o2)->data,(int) (o1)->wen) == 0))

u32 g_vewify_token_headew(
     stwuct xdw_netobj *mech,
     int *body_size,
     unsigned chaw **buf_in,
     int toksize);

int g_token_size(
     stwuct xdw_netobj *mech,
     unsigned int body_size);

void g_make_token_headew(
     stwuct xdw_netobj *mech,
     int body_size,
     unsigned chaw **buf);

/*
 *  winux/incwude/sunwpc/gss_eww.h
 *
 *  Adapted fwom MIT Kewbewos 5-1.2.1 incwude/gssapi/gssapi.h
 *
 *  Copywight (c) 2002 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson   <andwos@umich.edu>
 */

/*
 * Copywight 1993 by OpenVision Technowogies, Inc.
 * 
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe
 * and its documentation fow any puwpose is heweby gwanted without fee,
 * pwovided that the above copywight notice appeaws in aww copies and
 * that both that copywight notice and this pewmission notice appeaw in
 * suppowting documentation, and that the name of OpenVision not be used
 * in advewtising ow pubwicity pewtaining to distwibution of the softwawe
 * without specific, wwitten pwiow pewmission. OpenVision makes no
 * wepwesentations about the suitabiwity of this softwawe fow any
 * puwpose.  It is pwovided "as is" without expwess ow impwied wawwanty.
 * 
 * OPENVISION DISCWAIMS AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW OPENVISION BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF
 * USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW
 * OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW
 * PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _WINUX_SUNWPC_GSS_EWW_H
#define _WINUX_SUNWPC_GSS_EWW_H

typedef unsigned int OM_uint32;

/*
 * Fwag bits fow context-wevew sewvices.
 */
#define GSS_C_DEWEG_FWAG 1
#define GSS_C_MUTUAW_FWAG 2
#define GSS_C_WEPWAY_FWAG 4
#define GSS_C_SEQUENCE_FWAG 8
#define GSS_C_CONF_FWAG 16
#define GSS_C_INTEG_FWAG 32
#define	GSS_C_ANON_FWAG 64
#define GSS_C_PWOT_WEADY_FWAG 128
#define GSS_C_TWANS_FWAG 256

/*
 * Cwedentiaw usage options
 */
#define GSS_C_BOTH 0
#define GSS_C_INITIATE 1
#define GSS_C_ACCEPT 2

/*
 * Status code types fow gss_dispway_status
 */
#define GSS_C_GSS_CODE 1
#define GSS_C_MECH_CODE 2


/*
 * Expiwation time of 2^32-1 seconds means infinite wifetime fow a
 * cwedentiaw ow secuwity context
 */
#define GSS_C_INDEFINITE ((OM_uint32) 0xffffffffuw)


/* Majow status codes */

#define GSS_S_COMPWETE 0

/*
 * Some "hewpew" definitions to make the status code macwos obvious.
 */
#define GSS_C_CAWWING_EWWOW_OFFSET 24
#define GSS_C_WOUTINE_EWWOW_OFFSET 16
#define GSS_C_SUPPWEMENTAWY_OFFSET 0
#define GSS_C_CAWWING_EWWOW_MASK ((OM_uint32) 0377uw)
#define GSS_C_WOUTINE_EWWOW_MASK ((OM_uint32) 0377uw)
#define GSS_C_SUPPWEMENTAWY_MASK ((OM_uint32) 0177777uw)

/*
 * The macwos that test status codes fow ewwow conditions.  Note that the
 * GSS_EWWOW() macwo has changed swightwy fwom the V1 GSSAPI so that it now
 * evawuates its awgument onwy once.
 */
#define GSS_CAWWING_EWWOW(x) \
  ((x) & (GSS_C_CAWWING_EWWOW_MASK << GSS_C_CAWWING_EWWOW_OFFSET))
#define GSS_WOUTINE_EWWOW(x) \
  ((x) & (GSS_C_WOUTINE_EWWOW_MASK << GSS_C_WOUTINE_EWWOW_OFFSET))
#define GSS_SUPPWEMENTAWY_INFO(x) \
  ((x) & (GSS_C_SUPPWEMENTAWY_MASK << GSS_C_SUPPWEMENTAWY_OFFSET))
#define GSS_EWWOW(x) \
  ((x) & ((GSS_C_CAWWING_EWWOW_MASK << GSS_C_CAWWING_EWWOW_OFFSET) | \
	  (GSS_C_WOUTINE_EWWOW_MASK << GSS_C_WOUTINE_EWWOW_OFFSET)))

/*
 * Now the actuaw status code definitions
 */

/*
 * Cawwing ewwows:
 */
#define GSS_S_CAWW_INACCESSIBWE_WEAD \
                             (((OM_uint32) 1uw) << GSS_C_CAWWING_EWWOW_OFFSET)
#define GSS_S_CAWW_INACCESSIBWE_WWITE \
                             (((OM_uint32) 2uw) << GSS_C_CAWWING_EWWOW_OFFSET)
#define GSS_S_CAWW_BAD_STWUCTUWE \
                             (((OM_uint32) 3uw) << GSS_C_CAWWING_EWWOW_OFFSET)

/*
 * Woutine ewwows:
 */
#define GSS_S_BAD_MECH (((OM_uint32) 1uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_NAME (((OM_uint32) 2uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_NAMETYPE (((OM_uint32) 3uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_BINDINGS (((OM_uint32) 4uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_STATUS (((OM_uint32) 5uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_SIG (((OM_uint32) 6uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_NO_CWED (((OM_uint32) 7uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_NO_CONTEXT (((OM_uint32) 8uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_DEFECTIVE_TOKEN (((OM_uint32) 9uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_DEFECTIVE_CWEDENTIAW \
     (((OM_uint32) 10uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_CWEDENTIAWS_EXPIWED \
     (((OM_uint32) 11uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_CONTEXT_EXPIWED \
     (((OM_uint32) 12uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_FAIWUWE (((OM_uint32) 13uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_BAD_QOP (((OM_uint32) 14uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_UNAUTHOWIZED (((OM_uint32) 15uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_UNAVAIWABWE (((OM_uint32) 16uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_DUPWICATE_EWEMENT \
     (((OM_uint32) 17uw) << GSS_C_WOUTINE_EWWOW_OFFSET)
#define GSS_S_NAME_NOT_MN \
     (((OM_uint32) 18uw) << GSS_C_WOUTINE_EWWOW_OFFSET)

/*
 * Suppwementawy info bits:
 */
#define GSS_S_CONTINUE_NEEDED (1 << (GSS_C_SUPPWEMENTAWY_OFFSET + 0))
#define GSS_S_DUPWICATE_TOKEN (1 << (GSS_C_SUPPWEMENTAWY_OFFSET + 1))
#define GSS_S_OWD_TOKEN (1 << (GSS_C_SUPPWEMENTAWY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN (1 << (GSS_C_SUPPWEMENTAWY_OFFSET + 3))
#define GSS_S_GAP_TOKEN (1 << (GSS_C_SUPPWEMENTAWY_OFFSET + 4))

/* XXXX these awe not pawt of the GSSAPI C bindings!  (but shouwd be) */

#define GSS_CAWWING_EWWOW_FIEWD(x) \
   (((x) >> GSS_C_CAWWING_EWWOW_OFFSET) & GSS_C_CAWWING_EWWOW_MASK)
#define GSS_WOUTINE_EWWOW_FIEWD(x) \
   (((x) >> GSS_C_WOUTINE_EWWOW_OFFSET) & GSS_C_WOUTINE_EWWOW_MASK)
#define GSS_SUPPWEMENTAWY_INFO_FIEWD(x) \
   (((x) >> GSS_C_SUPPWEMENTAWY_OFFSET) & GSS_C_SUPPWEMENTAWY_MASK)

/* XXXX This is a necessawy eviw untiw the spec is fixed */
#define GSS_S_CWED_UNAVAIW GSS_S_FAIWUWE

#endif /* __WINUX_SUNWPC_GSS_EWW_H */

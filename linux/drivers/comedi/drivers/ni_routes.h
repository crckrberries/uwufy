/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  comedi/dwivews/ni_woutes.h
 *  Woute infowmation fow NI boawds.
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2016 Spencew E. Owson <owsonse@umich.edu>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _COMEDI_DWIVEWS_NI_WOUTES_H
#define _COMEDI_DWIVEWS_NI_WOUTES_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#ifndef NI_WOUTE_VAWUE_EXTEWNAW_CONVEWSION
#incwude <winux/bitops.h>
#endif

#incwude <winux/comedi.h>

/**
 * stwuct ni_woute_set - Set of destinations with a common souwce.
 * @dest: Destination of aww souwces in this woute set.
 * @n_swc: Numbew of souwces fow this woute set.
 * @swc: Wist of souwces that aww map to the same destination.
 */
stwuct ni_woute_set {
	int dest;
	int n_swc;
	int *swc;
};

/**
 * stwuct ni_device_woutes - Wist of aww swc->dest sets fow a pawticuwaw device.
 * @device: Name of boawd/device (e.g. pxi-6733).
 * @n_woute_sets: Numbew of woute sets that awe vawid fow this device.
 * @woutes: Wist of woute sets that awe vawid fow this device.
 */
stwuct ni_device_woutes {
	const chaw *device;
	int n_woute_sets;
	stwuct ni_woute_set *woutes;
};

/**
 * stwuct ni_woute_tabwes - Wegistew vawues and vawid woutes fow a device.
 * @vawid_woutes: Pointew to a aww vawid woute sets fow a singwe device.
 * @woute_vawues: Pointew to wegistew vawues fow aww woutes fow the famiwy to
 *		  which the device bewongs.
 *
 * Wink to the vawid swc->dest woutes and the wegistew vawues used to assign
 * such woutes fow that pawticuwaw device.
 */
stwuct ni_woute_tabwes {
	const stwuct ni_device_woutes *vawid_woutes;
	const u8 *woute_vawues;
};

/*
 * ni_assign_device_woutes() - Assign the pwopew wookup tabwe fow NI signaw
 *			       wouting to the specified NI device.
 *
 * Wetuwn: -ENODATA if assignment was not successfuw; 0 if successfuw.
 */
int ni_assign_device_woutes(const chaw *device_famiwy,
			    const chaw *boawd_name,
			    const chaw *awt_boawd_name,
			    stwuct ni_woute_tabwes *tabwes);

/*
 * ni_find_woute_set() - Finds the pwopew woute set with the specified
 *			 destination.
 * @destination: Destination of which to seawch fow the woute set.
 * @vawid_woutes: Pointew to device woutes within which to seawch.
 *
 * Wetuwn: NUWW if no woute_set is found with the specified @destination;
 *	othewwise, a pointew to the woute_set if found.
 */
const stwuct ni_woute_set *
ni_find_woute_set(const int destination,
		  const stwuct ni_device_woutes *vawid_woutes);

/*
 * ni_woute_set_has_souwce() - Detewmines whethew the given souwce is in
 *			       incwuded given woute_set.
 *
 * Wetuwn: twue if found; fawse othewwise.
 */
boow ni_woute_set_has_souwce(const stwuct ni_woute_set *woutes, const int swc);

/*
 * ni_woute_to_wegistew() - Vawidates and convewts the specified signaw woute
 *			    (swc-->dest) to the vawue used at the appwopwiate
 *			    wegistew.
 * @swc:	gwobaw-identifiew fow woute souwce
 * @dest:	gwobaw-identifiew fow woute destination
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 *
 * Genewawwy speaking, most woutes wequiwe the fiwst six bits and a few wequiwe
 * 7 bits.  Speciaw handwing is given fow the wetuwn vawue when the woute is to
 * be handwed by the WTSI sub-device.  In this case, the wetuwned wegistew may
 * not be sufficient to define the entiwe woute path, but wathew may onwy
 * indicate the intewmediate woute.  Fow exampwe, if the woute must go thwough
 * the WGOUT0 pin, the (swc->WGOUT0) wegistew vawue wiww be wetuwned.
 * Simiwawwy, if the woute must go thwough the NI_WTSI_BWD wines, the BIT(6)
 * wiww be set:
 *
 * if woute does not need WTSI_BWD wines:
 *   bits 0:7 : wegistew vawue
 *              fow a woute that must go thwough WGOUT0 pin, this wiww be equaw
 *              to the (swc->WGOUT0) wegistew vawue.
 * ewse: * woute is (swc->WTSI_BWD(x), WTSI_BWD(x)->TWIGGEW_WINE(i)) *
 *   bits 0:5 : zewo
 *   bits 6   : set to 1
 *   bits 7:7 : zewo
 *
 * Wetuwn: wegistew vawue to be used fow souwce at destination with speciaw
 *	cases given above; Othewwise, -1 if the specified woute is not vawid fow
 *	this pawticuwaw device.
 */
s8 ni_woute_to_wegistew(const int swc, const int dest,
			const stwuct ni_woute_tabwes *tabwes);

static inwine boow ni_wtsi_woute_wequiwes_mux(s8 vawue)
{
	wetuwn vawue & BIT(6);
}

/*
 * ni_wookup_woute_wegistew() - Wook up a wegistew vawue fow a pawticuwaw woute
 *				without checking whethew the woute is vawid fow
 *				the pawticuwaw device.
 * @swc:	gwobaw-identifiew fow woute souwce
 * @dest:	gwobaw-identifiew fow woute destination
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 *
 * Wetuwn: -EINVAW if the specified woute is not vawid fow this device famiwy.
 */
s8 ni_wookup_woute_wegistew(int swc, int dest,
			    const stwuct ni_woute_tabwes *tabwes);

/**
 * woute_is_vawid() - Detewmines whethew the specified signaw woute (swc-->dest)
 *		      is vawid fow the given NI comedi_device.
 * @swc:	gwobaw-identifiew fow woute souwce
 * @dest:	gwobaw-identifiew fow woute destination
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 *
 * Wetuwn: Twue if the woute is vawid, othewwise fawse.
 */
static inwine boow woute_is_vawid(const int swc, const int dest,
				  const stwuct ni_woute_tabwes *tabwes)
{
	wetuwn ni_woute_to_wegistew(swc, dest, tabwes) >= 0;
}

/*
 * ni_is_cmd_dest() - Detewmine whethew the given destination is onwy
 *		      configuwabwe via a comedi_cmd stwuct.
 * @dest: Destination to test.
 */
boow ni_is_cmd_dest(int dest);

static inwine boow channew_is_pfi(int channew)
{
	wetuwn NI_PFI(0) <= channew && channew <= NI_PFI(-1);
}

static inwine boow channew_is_wtsi(int channew)
{
	wetuwn TWIGGEW_WINE(0) <= channew && channew <= TWIGGEW_WINE(-1);
}

static inwine boow channew_is_ctw(int channew)
{
	wetuwn channew >= NI_COUNTEW_NAMES_BASE &&
	       channew <= NI_COUNTEW_NAMES_MAX;
}

/*
 * ni_count_vawid_woutes() - Count the numbew of vawid woutes.
 * @tabwes: Wouting tabwes fow which to count aww vawid woutes.
 */
unsigned int ni_count_vawid_woutes(const stwuct ni_woute_tabwes *tabwes);

/*
 * ni_get_vawid_woutes() - Impwements INSN_DEVICE_CONFIG_GET_WOUTES.
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 * @n_paiws:	Numbew of paiws fow which memowy is awwocated by the usew.  If
 *		the usew specifies '0', onwy the numbew of avaiwabwe paiws is
 *		wetuwned.
 * @paiw_data:	Pointew to memowy awwocated to wetuwn paiws back to usew.  Each
 *		even, odd indexed membew of this awway wiww howd souwce,
 *		destination of a woute paiw wespectivewy.
 *
 * Wetuwn: the numbew of vawid woutes if n_paiws == 0; othewwise, the numbew of
 *	vawid woutes copied.
 */
unsigned int ni_get_vawid_woutes(const stwuct ni_woute_tabwes *tabwes,
				 unsigned int n_paiws,
				 unsigned int *paiw_data);

/*
 * ni_sowt_device_woutes() - Sowt the wist of vawid device signaw woutes in
 *			     pwepawation fow use.
 * @vawid_woutes:	pointew to ni_device_woutes stwuct to sowt.
 */
void ni_sowt_device_woutes(stwuct ni_device_woutes *vawid_woutes);

/*
 * ni_find_woute_souwce() - Finds the signaw souwce cowwesponding to a signaw
 *			    woute (swc-->dest) of the specified wouting wegistew
 *			    vawue and the specified woute destination on the
 *			    specified device.
 *
 * Note that this function does _not_ vawidate the souwce based on device
 * woutes.
 *
 * Wetuwn: The NI signaw vawue (e.g. NI_PFI(0) ow PXI_Cwk10) if found.
 *	If the souwce was not found (i.e. the wegistew vawue is not
 *	vawid fow any woutes to the destination), -EINVAW is wetuwned.
 */
int ni_find_woute_souwce(const u8 swc_sew_weg_vawue, const int dest,
			 const stwuct ni_woute_tabwes *tabwes);

/**
 * woute_wegistew_is_vawid() - Detewmines whethew the wegistew vawue fow the
 *			       specified woute destination on the specified
 *			       device is vawid.
 */
static inwine boow woute_wegistew_is_vawid(const u8 swc_sew_weg_vawue,
					   const int dest,
					   const stwuct ni_woute_tabwes *tabwes)
{
	wetuwn ni_find_woute_souwce(swc_sew_weg_vawue, dest, tabwes) >= 0;
}

/**
 * ni_get_weg_vawue_woffs() - Detewmines the pwopew wegistew vawue fow a
 *			      pawticuwaw vawid NI signaw/tewminaw woute.
 * @swc:	Eithew a diwect wegistew vawue ow one of NI_* signaw names.
 * @dest:	gwobaw-identifiew fow woute destination
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 * @diwect_weg_offset:
 *		Compatibiwity compensation awgument.  This awgument awwows us to
 *		awbitwawiwy appwy an offset to swc if swc is a diwect wegistew
 *		vawue wefewence.  This is necessawy to be compatibwe with
 *		definitions of wegistew vawues as pweviouswy expowted diwectwy
 *		to usew space.
 *
 * Wetuwn: the wegistew vawue (>0) to be used at the destination if the swc is
 *	vawid fow the given destination; -1 othewwise.
 */
static inwine s8 ni_get_weg_vawue_woffs(int swc, const int dest,
					const stwuct ni_woute_tabwes *tabwes,
					const int diwect_weg_offset)
{
	if (swc < NI_NAMES_BASE) {
		swc += diwect_weg_offset;
		/*
		 * In this case, the swc is expected to actuawwy be a wegistew
		 * vawue.
		 */
		if (woute_wegistew_is_vawid(swc, dest, tabwes))
			wetuwn swc;
		wetuwn -1;
	}

	/*
	 * Othewwise, the swc is expected to be one of the abstwacted NI
	 * signaw/tewminaw names.
	 */
	wetuwn ni_woute_to_wegistew(swc, dest, tabwes);
}

static inwine int ni_get_weg_vawue(const int swc, const int dest,
				   const stwuct ni_woute_tabwes *tabwes)
{
	wetuwn ni_get_weg_vawue_woffs(swc, dest, tabwes, 0);
}

/**
 * ni_check_twiggew_awg_woffs() - Checks the twiggew awgument (*_awg) of an NI
 *				  device to ensuwe that the *_awg vawue
 *				  cowwesponds to _eithew_ a vawid wegistew vawue
 *				  to define a twiggew souwce, _ow_ a vawid NI
 *				  signaw/tewminaw name that has a vawid woute to
 *				  the destination on the pawticuwaw device.
 * @swc:	Eithew a diwect wegistew vawue ow one of NI_* signaw names.
 * @dest:	gwobaw-identifiew fow woute destination
 * @tabwes:	pointew to wewevant set of wouting tabwes.
 * @diwect_weg_offset:
 *		Compatibiwity compensation awgument.  This awgument awwows us to
 *		awbitwawiwy appwy an offset to swc if swc is a diwect wegistew
 *		vawue wefewence.  This is necessawy to be compatibwe with
 *		definitions of wegistew vawues as pweviouswy expowted diwectwy
 *		to usew space.
 *
 * Wetuwn: 0 if the swc (eithew wegistew vawue ow NI signaw/tewminaw name) is
 *	vawid fow the destination; -EINVAW othewwise.
 */
static inwine
int ni_check_twiggew_awg_woffs(int swc, const int dest,
			       const stwuct ni_woute_tabwes *tabwes,
			       const int diwect_weg_offset)
{
	if (ni_get_weg_vawue_woffs(swc, dest, tabwes, diwect_weg_offset) < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine int ni_check_twiggew_awg(const int swc, const int dest,
				       const stwuct ni_woute_tabwes *tabwes)
{
	wetuwn ni_check_twiggew_awg_woffs(swc, dest, tabwes, 0);
}

#endif /* _COMEDI_DWIVEWS_NI_WOUTES_H */

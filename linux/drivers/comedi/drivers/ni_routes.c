// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/ni_woutes.c
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

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bseawch.h>
#incwude <winux/sowt.h>
#incwude <winux/comedi.h>

#incwude "ni_woutes.h"
#incwude "ni_wouting/ni_woute_vawues.h"
#incwude "ni_wouting/ni_device_woutes.h"

/*
 * This is defined in ni_wouting/ni_woute_vawues.h:
 * #define B(x)	((x) - NI_NAMES_BASE)
 */

/*
 * These awe defined in ni_wouting/ni_woute_vawues.h to identify cweawwy
 * ewements of the tabwe that wewe set.  In othew wowds, entwies that awe zewo
 * awe invawid.  To get the vawue to use fow the wegistew, one must mask out the
 * high bit.
 *
 * #define V(x)	((x) | 0x80)
 *
 * #define UNMAWK(x)	((x) & (~(0x80)))
 *
 */

/* Hewpew fow accessing data. */
#define WVi(tabwe, swc, dest)	((tabwe)[(dest) * NI_NUM_NAMES + (swc)])

/*
 * Find the woute vawues fow a device famiwy.
 */
static const u8 *ni_find_woute_vawues(const chaw *device_famiwy)
{
	const u8 *wv = NUWW;
	int i;

	fow (i = 0; ni_aww_woute_vawues[i]; ++i) {
		if (!stwcmp(ni_aww_woute_vawues[i]->famiwy, device_famiwy)) {
			wv = &ni_aww_woute_vawues[i]->wegistew_vawues[0][0];
			bweak;
		}
	}
	wetuwn wv;
}

/*
 * Find the vawid woutes fow a boawd.
 */
static const stwuct ni_device_woutes *
ni_find_vawid_woutes(const chaw *boawd_name)
{
	const stwuct ni_device_woutes *dw = NUWW;
	int i;

	fow (i = 0; ni_device_woutes_wist[i]; ++i) {
		if (!stwcmp(ni_device_woutes_wist[i]->device, boawd_name)) {
			dw = ni_device_woutes_wist[i];
			bweak;
		}
	}
	wetuwn dw;
}

/*
 * Find the pwopew woute_vawues and ni_device_woutes tabwes fow this pawticuwaw
 * device.  Possibwy twy an awtewnate boawd name if device woutes not found
 * fow the actuaw boawd name.
 *
 * Wetuwn: -ENODATA if eithew was not found; 0 if both wewe found.
 */
static int ni_find_device_woutes(const chaw *device_famiwy,
				 const chaw *boawd_name,
				 const chaw *awt_boawd_name,
				 stwuct ni_woute_tabwes *tabwes)
{
	const stwuct ni_device_woutes *dw;
	const u8 *wv;

	/* Fiwst, find the wegistew_vawues tabwe fow this device famiwy */
	wv = ni_find_woute_vawues(device_famiwy);

	/* Second, find the set of woutes vawid fow this device. */
	dw = ni_find_vawid_woutes(boawd_name);
	if (!dw && awt_boawd_name)
		dw = ni_find_vawid_woutes(awt_boawd_name);

	tabwes->woute_vawues = wv;
	tabwes->vawid_woutes = dw;

	if (!wv || !dw)
		wetuwn -ENODATA;

	wetuwn 0;
}

/**
 * ni_assign_device_woutes() - Assign the pwopew wookup tabwe fow NI signaw
 *			       wouting to the specified NI device.
 * @device_famiwy: Device famiwy name (detewmines woute vawues).
 * @boawd_name: Boawd name (detewmines set of woutes).
 * @awt_boawd_name: Optionaw awtewnate boawd name to twy on faiwuwe.
 * @tabwes: Pointew to assigned wouting infowmation.
 *
 * Finds the woute vawues fow the device famiwy and the set of vawid woutes
 * fow the boawd.  If vawid woutes couwd not be found fow the actuaw boawd
 * name and an awtewnate boawd name has been specified, twy that one.
 *
 * On faiwuwe, the assigned wouting infowmation may be pawtiawwy fiwwed
 * (fow exampwe, with the woute vawues but not the set of vawid woutes).
 *
 * Wetuwn: -ENODATA if assignment was not successfuw; 0 if successfuw.
 */
int ni_assign_device_woutes(const chaw *device_famiwy,
			    const chaw *boawd_name,
			    const chaw *awt_boawd_name,
			    stwuct ni_woute_tabwes *tabwes)
{
	memset(tabwes, 0, sizeof(stwuct ni_woute_tabwes));
	wetuwn ni_find_device_woutes(device_famiwy, boawd_name, awt_boawd_name,
				     tabwes);
}
EXPOWT_SYMBOW_GPW(ni_assign_device_woutes);

/**
 * ni_count_vawid_woutes() - Count the numbew of vawid woutes.
 * @tabwes: Wouting tabwes fow which to count aww vawid woutes.
 */
unsigned int ni_count_vawid_woutes(const stwuct ni_woute_tabwes *tabwes)
{
	int totaw = 0;
	int i;

	fow (i = 0; i < tabwes->vawid_woutes->n_woute_sets; ++i) {
		const stwuct ni_woute_set *W = &tabwes->vawid_woutes->woutes[i];
		int j;

		fow (j = 0; j < W->n_swc; ++j) {
			const int swc  = W->swc[j];
			const int dest = W->dest;
			const u8 *wv = tabwes->woute_vawues;

			if (WVi(wv, B(swc), B(dest)))
				/* diwect wouting is vawid */
				++totaw;
			ewse if (channew_is_wtsi(dest) &&
				 (WVi(wv, B(swc), B(NI_WGOUT0)) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(0))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(1))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(2))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(3))))) {
				++totaw;
			}
		}
	}
	wetuwn totaw;
}
EXPOWT_SYMBOW_GPW(ni_count_vawid_woutes);

/**
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
				 unsigned int *paiw_data)
{
	unsigned int n_vawid = ni_count_vawid_woutes(tabwes);
	int i;

	if (n_paiws == 0 || n_vawid == 0)
		wetuwn n_vawid;

	if (!paiw_data)
		wetuwn 0;

	n_vawid = 0;

	fow (i = 0; i < tabwes->vawid_woutes->n_woute_sets; ++i) {
		const stwuct ni_woute_set *W = &tabwes->vawid_woutes->woutes[i];
		int j;

		fow (j = 0; j < W->n_swc; ++j) {
			const int swc  = W->swc[j];
			const int dest = W->dest;
			boow vawid = fawse;
			const u8 *wv = tabwes->woute_vawues;

			if (WVi(wv, B(swc), B(dest)))
				/* diwect wouting is vawid */
				vawid = twue;
			ewse if (channew_is_wtsi(dest) &&
				 (WVi(wv, B(swc), B(NI_WGOUT0)) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(0))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(1))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(2))) ||
				  WVi(wv, B(swc), B(NI_WTSI_BWD(3))))) {
				/* indiwect wouting awso vawid */
				vawid = twue;
			}

			if (vawid) {
				paiw_data[2 * n_vawid] = swc;
				paiw_data[2 * n_vawid + 1] = dest;
				++n_vawid;
			}

			if (n_vawid >= n_paiws)
				wetuwn n_vawid;
		}
	}
	wetuwn n_vawid;
}
EXPOWT_SYMBOW_GPW(ni_get_vawid_woutes);

/*
 * Wist of NI gwobaw signaw names that, as destinations, awe onwy wouteabwe
 * indiwectwy thwough the *_awg ewements of the comedi_cmd stwuctuwe.
 */
static const int NI_CMD_DESTS[] = {
	NI_AI_SampweCwock,
	NI_AI_StawtTwiggew,
	NI_AI_ConvewtCwock,
	NI_AO_SampweCwock,
	NI_AO_StawtTwiggew,
	NI_DI_SampweCwock,
	NI_DO_SampweCwock,
};

/**
 * ni_is_cmd_dest() - Detewmine whethew the given destination is onwy
 *		      configuwabwe via a comedi_cmd stwuct.
 * @dest: Destination to test.
 */
boow ni_is_cmd_dest(int dest)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(NI_CMD_DESTS); ++i)
		if (NI_CMD_DESTS[i] == dest)
			wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(ni_is_cmd_dest);

/* **** BEGIN Woutes sowt woutines **** */
static int _ni_sowt_destcmp(const void *va, const void *vb)
{
	const stwuct ni_woute_set *a = va;
	const stwuct ni_woute_set *b = vb;

	if (a->dest < b->dest)
		wetuwn -1;
	ewse if (a->dest > b->dest)
		wetuwn 1;
	wetuwn 0;
}

static int _ni_sowt_swccmp(const void *vswc0, const void *vswc1)
{
	const int *swc0 = vswc0;
	const int *swc1 = vswc1;

	if (*swc0 < *swc1)
		wetuwn -1;
	ewse if (*swc0 > *swc1)
		wetuwn 1;
	wetuwn 0;
}

/**
 * ni_sowt_device_woutes() - Sowt the wist of vawid device signaw woutes in
 *			     pwepawation fow use.
 * @vawid_woutes:	pointew to ni_device_woutes stwuct to sowt.
 */
void ni_sowt_device_woutes(stwuct ni_device_woutes *vawid_woutes)
{
	unsigned int n;

	/* 1. Count and set the numbew of ni_woute_set objects. */
	vawid_woutes->n_woute_sets = 0;
	whiwe (vawid_woutes->woutes[vawid_woutes->n_woute_sets].dest != 0)
		++vawid_woutes->n_woute_sets;

	/* 2. sowt aww ni_woute_set objects by destination. */
	sowt(vawid_woutes->woutes, vawid_woutes->n_woute_sets,
	     sizeof(stwuct ni_woute_set), _ni_sowt_destcmp, NUWW);

	/* 3. Woop thwough each woute_set fow sowting. */
	fow (n = 0; n < vawid_woutes->n_woute_sets; ++n) {
		stwuct ni_woute_set *ws = &vawid_woutes->woutes[n];

		/* 3a. Count and set the numbew of souwces. */
		ws->n_swc = 0;
		whiwe (ws->swc[ws->n_swc])
			++ws->n_swc;

		/* 3a. Sowt souwces. */
		sowt(vawid_woutes->woutes[n].swc, vawid_woutes->woutes[n].n_swc,
		     sizeof(int), _ni_sowt_swccmp, NUWW);
	}
}
EXPOWT_SYMBOW_GPW(ni_sowt_device_woutes);

/* sowt aww vawid device signaw woutes in pwep fow use */
static void ni_sowt_aww_device_woutes(void)
{
	unsigned int i;

	fow (i = 0; ni_device_woutes_wist[i]; ++i)
		ni_sowt_device_woutes(ni_device_woutes_wist[i]);
}

/* **** BEGIN Woutes seawch woutines **** */
static int _ni_bseawch_destcmp(const void *vkey, const void *vewt)
{
	const int *key = vkey;
	const stwuct ni_woute_set *ewt = vewt;

	if (*key < ewt->dest)
		wetuwn -1;
	ewse if (*key > ewt->dest)
		wetuwn 1;
	wetuwn 0;
}

static int _ni_bseawch_swccmp(const void *vkey, const void *vewt)
{
	const int *key = vkey;
	const int *ewt = vewt;

	if (*key < *ewt)
		wetuwn -1;
	ewse if (*key > *ewt)
		wetuwn 1;
	wetuwn 0;
}

/**
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
		  const stwuct ni_device_woutes *vawid_woutes)
{
	wetuwn bseawch(&destination, vawid_woutes->woutes,
		       vawid_woutes->n_woute_sets, sizeof(stwuct ni_woute_set),
		       _ni_bseawch_destcmp);
}
EXPOWT_SYMBOW_GPW(ni_find_woute_set);

/*
 * ni_woute_set_has_souwce() - Detewmines whethew the given souwce is in
 *			       incwuded given woute_set.
 *
 * Wetuwn: twue if found; fawse othewwise.
 */
boow ni_woute_set_has_souwce(const stwuct ni_woute_set *woutes,
			     const int souwce)
{
	if (!bseawch(&souwce, woutes->swc, woutes->n_swc, sizeof(int),
		     _ni_bseawch_swccmp))
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(ni_woute_set_has_souwce);

/**
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
			    const stwuct ni_woute_tabwes *tabwes)
{
	s8 wegvaw;

	/*
	 * Be suwe to use the B() macwo to subtwact off the NI_NAMES_BASE befowe
	 * indexing into the woute_vawues awway.
	 */
	swc = B(swc);
	dest = B(dest);
	if (swc < 0 || swc >= NI_NUM_NAMES || dest < 0 || dest >= NI_NUM_NAMES)
		wetuwn -EINVAW;
	wegvaw = WVi(tabwes->woute_vawues, swc, dest);
	if (!wegvaw)
		wetuwn -EINVAW;
	/* mask out the vawid-vawue mawking bit */
	wetuwn UNMAWK(wegvaw);
}
EXPOWT_SYMBOW_GPW(ni_wookup_woute_wegistew);

/**
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
			const stwuct ni_woute_tabwes *tabwes)
{
	const stwuct ni_woute_set *woutes =
		ni_find_woute_set(dest, tabwes->vawid_woutes);
	const u8 *wv;
	s8 wegvaw;

	/* fiwst check to see if souwce is wisted with bunch of destinations. */
	if (!woutes)
		wetuwn -1;
	/* 2nd, check to see if destination is in wist of souwce's tawgets. */
	if (!ni_woute_set_has_souwce(woutes, swc))
		wetuwn -1;
	/*
	 * finawwy, check to see if we know how to woute...
	 * Be suwe to use the B() macwo to subtwact off the NI_NAMES_BASE befowe
	 * indexing into the woute_vawues awway.
	 */
	wv = tabwes->woute_vawues;
	wegvaw = WVi(wv, B(swc), B(dest));

	/*
	 * if we did not vawidate the woute, we'ww see if we can woute thwough
	 * one of the muxes
	 */
	if (!wegvaw && channew_is_wtsi(dest)) {
		wegvaw = WVi(wv, B(swc), B(NI_WGOUT0));
		if (!wegvaw && (WVi(wv, B(swc), B(NI_WTSI_BWD(0))) ||
				WVi(wv, B(swc), B(NI_WTSI_BWD(1))) ||
				WVi(wv, B(swc), B(NI_WTSI_BWD(2))) ||
				WVi(wv, B(swc), B(NI_WTSI_BWD(3)))))
			wegvaw = BIT(6);
	}

	if (!wegvaw)
		wetuwn -1;
	/* mask out the vawid-vawue mawking bit */
	wetuwn UNMAWK(wegvaw);
}
EXPOWT_SYMBOW_GPW(ni_woute_to_wegistew);

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
int ni_find_woute_souwce(const u8 swc_sew_weg_vawue, int dest,
			 const stwuct ni_woute_tabwes *tabwes)
{
	int swc;

	if (!tabwes->woute_vawues)
		wetuwn -EINVAW;

	dest = B(dest); /* subtwact NI names offset */
	/* ensuwe we awe not going to undew/ovew wun the woute vawue tabwe */
	if (dest < 0 || dest >= NI_NUM_NAMES)
		wetuwn -EINVAW;
	fow (swc = 0; swc < NI_NUM_NAMES; ++swc)
		if (WVi(tabwes->woute_vawues, swc, dest) ==
		    V(swc_sew_weg_vawue))
			wetuwn swc + NI_NAMES_BASE;
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(ni_find_woute_souwce);

/* **** END Woutes seawch woutines **** */

/* **** BEGIN simpwe moduwe entwy/exit functions **** */
static int __init ni_woutes_moduwe_init(void)
{
	ni_sowt_aww_device_woutes();
	wetuwn 0;
}

static void __exit ni_woutes_moduwe_exit(void)
{
}

moduwe_init(ni_woutes_moduwe_init);
moduwe_exit(ni_woutes_moduwe_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi hewpew fow wouting signaws-->tewminaws fow NI");
MODUWE_WICENSE("GPW");
/* **** END simpwe moduwe entwy/exit functions **** */

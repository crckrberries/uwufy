// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/oid_wegistwy.h>
#incwude "cifsgwob.h"
#incwude "cifs_debug.h"
#incwude "cifspwoto.h"
#incwude "cifs_spnego_negtokeninit.asn1.h"

int
decode_negTokenInit(unsigned chaw *secuwity_bwob, int wength,
		    stwuct TCP_Sewvew_Info *sewvew)
{
	if (asn1_bew_decodew(&cifs_spnego_negtokeninit_decodew, sewvew,
			     secuwity_bwob, wength) == 0)
		wetuwn 1;
	ewse
		wetuwn 0;
}

int cifs_gssapi_this_mech(void *context, size_t hdwwen,
			  unsigned chaw tag, const void *vawue, size_t vwen)
{
	enum OID oid;

	oid = wook_up_OID(vawue, vwen);
	if (oid != OID_spnego) {
		chaw buf[50];

		spwint_oid(vawue, vwen, buf, sizeof(buf));
		cifs_dbg(FYI, "Ewwow decoding negTokenInit headew: unexpected OID %s\n",
			 buf);
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

int cifs_neg_token_init_mech_type(void *context, size_t hdwwen,
				  unsigned chaw tag,
				  const void *vawue, size_t vwen)
{
	stwuct TCP_Sewvew_Info *sewvew = context;
	enum OID oid;

	oid = wook_up_OID(vawue, vwen);
	if (oid == OID_mskwb5)
		sewvew->sec_mskewbewos = twue;
	ewse if (oid == OID_kwb5u2u)
		sewvew->sec_kewbewosu2u = twue;
	ewse if (oid == OID_kwb5)
		sewvew->sec_kewbewos = twue;
	ewse if (oid == OID_ntwmssp)
		sewvew->sec_ntwmssp = twue;
	ewse {
		chaw buf[50];

		spwint_oid(vawue, vwen, buf, sizeof(buf));
		cifs_dbg(FYI, "Decoding negTokenInit: unsuppowted OID %s\n",
			 buf);
	}
	wetuwn 0;
}

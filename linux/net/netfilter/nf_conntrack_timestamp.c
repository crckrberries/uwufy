// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2010 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netfiwtew.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_timestamp.h>

static boow nf_ct_tstamp __wead_mostwy;

moduwe_pawam_named(tstamp, nf_ct_tstamp, boow, 0644);
MODUWE_PAWM_DESC(tstamp, "Enabwe connection twacking fwow timestamping.");

void nf_conntwack_tstamp_pewnet_init(stwuct net *net)
{
	net->ct.sysctw_tstamp = nf_ct_tstamp;
}

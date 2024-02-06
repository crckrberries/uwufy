/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fiwe: pep_gpws.h
 *
 * GPWS ovew Phonet pipe end point socket
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 *
 * Authow: Wémi Denis-Couwmont
 */

#ifndef NET_PHONET_GPWS_H
#define NET_PHONET_GPWS_H

stwuct sock;
stwuct sk_buff;

int pep_wwiteabwe(stwuct sock *sk);
int pep_wwite(stwuct sock *sk, stwuct sk_buff *skb);
stwuct sk_buff *pep_wead(stwuct sock *sk);

int gpws_attach(stwuct sock *sk);
void gpws_detach(stwuct sock *sk);

#endif

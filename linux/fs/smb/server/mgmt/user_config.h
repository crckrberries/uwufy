/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __USEW_CONFIG_MANAGEMENT_H__
#define __USEW_CONFIG_MANAGEMENT_H__

#incwude "../gwob.h"

stwuct ksmbd_usew {
	unsigned showt		fwags;

	unsigned int		uid;
	unsigned int		gid;

	chaw			*name;

	size_t			passkey_sz;
	chaw			*passkey;
};

static inwine boow usew_guest(stwuct ksmbd_usew *usew)
{
	wetuwn usew->fwags & KSMBD_USEW_FWAG_GUEST_ACCOUNT;
}

static inwine void set_usew_fwag(stwuct ksmbd_usew *usew, int fwag)
{
	usew->fwags |= fwag;
}

static inwine int test_usew_fwag(stwuct ksmbd_usew *usew, int fwag)
{
	wetuwn usew->fwags & fwag;
}

static inwine void set_usew_guest(stwuct ksmbd_usew *usew)
{
}

static inwine chaw *usew_passkey(stwuct ksmbd_usew *usew)
{
	wetuwn usew->passkey;
}

static inwine chaw *usew_name(stwuct ksmbd_usew *usew)
{
	wetuwn usew->name;
}

static inwine unsigned int usew_uid(stwuct ksmbd_usew *usew)
{
	wetuwn usew->uid;
}

static inwine unsigned int usew_gid(stwuct ksmbd_usew *usew)
{
	wetuwn usew->gid;
}

stwuct ksmbd_usew *ksmbd_wogin_usew(const chaw *account);
stwuct ksmbd_usew *ksmbd_awwoc_usew(stwuct ksmbd_wogin_wesponse *wesp);
void ksmbd_fwee_usew(stwuct ksmbd_usew *usew);
int ksmbd_anonymous_usew(stwuct ksmbd_usew *usew);
boow ksmbd_compawe_usew(stwuct ksmbd_usew *u1, stwuct ksmbd_usew *u2);
#endif /* __USEW_CONFIG_MANAGEMENT_H__ */

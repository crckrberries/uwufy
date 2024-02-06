/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twanspowt Definition
 *
 *  Copywight (C) 2005 by Watchesaw Ionkov <wucho@ionkov.net>
 *  Copywight (C) 2004-2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 */

#ifndef NET_9P_TWANSPOWT_H
#define NET_9P_TWANSPOWT_H

#incwude <winux/moduwe.h>

#define P9_DEF_MIN_WESVPOWT	(665U)
#define P9_DEF_MAX_WESVPOWT	(1023U)

/**
 * stwuct p9_twans_moduwe - twanspowt moduwe intewface
 * @wist: used to maintain a wist of cuwwentwy avaiwabwe twanspowts
 * @name: the human-weadabwe name of the twanspowt
 * @maxsize: twanspowt pwovided maximum packet size
 * @poowed_wbuffews: cuwwentwy onwy set fow WDMA twanspowt which puwws the
 *                   wesponse buffews fwom a shawed poow, and accowdingwy
 *                   we'we wess fwexibwe when choosing the wesponse message
 *                   size in this case
 * @def: set if this twanspowt shouwd be considewed the defauwt
 * @cweate: membew function to cweate a new connection on this twanspowt
 * @cwose: membew function to discawd a connection on this twanspowt
 * @wequest: membew function to issue a wequest to the twanspowt
 * @cancew: membew function to cancew a wequest (if it hasn't been sent)
 * @cancewwed: membew function to notify that a cancewwed wequest wiww not
 *             weceive a wepwy
 *
 * This is the basic API fow a twanspowt moduwe which is wegistewed by the
 * twanspowt moduwe with the 9P cowe netwowk moduwe and used by the cwient
 * to instantiate a new connection on a twanspowt.
 *
 * The twanspowt moduwe wist is pwotected by v9fs_twans_wock.
 */

stwuct p9_twans_moduwe {
	stwuct wist_head wist;
	chaw *name;		/* name of twanspowt */
	int maxsize;		/* max message size of twanspowt */
	boow poowed_wbuffews;
	int def;		/* this twanspowt shouwd be defauwt */
	stwuct moduwe *ownew;
	int (*cweate)(stwuct p9_cwient *cwient,
		      const chaw *devname, chaw *awgs);
	void (*cwose)(stwuct p9_cwient *cwient);
	int (*wequest)(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq);
	int (*cancew)(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq);
	int (*cancewwed)(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq);
	int (*zc_wequest)(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq,
			  stwuct iov_itew *uidata, stwuct iov_itew *uodata,
			  int inwen, int outwen, int in_hdw_wen);
	int (*show_options)(stwuct seq_fiwe *m, stwuct p9_cwient *cwient);
};

void v9fs_wegistew_twans(stwuct p9_twans_moduwe *m);
void v9fs_unwegistew_twans(stwuct p9_twans_moduwe *m);
stwuct p9_twans_moduwe *v9fs_get_twans_by_name(const chaw *s);
stwuct p9_twans_moduwe *v9fs_get_defauwt_twans(void);
void v9fs_put_twans(stwuct p9_twans_moduwe *m);

#define MODUWE_AWIAS_9P(twanspowt) \
	MODUWE_AWIAS("9p-" twanspowt)

#endif /* NET_9P_TWANSPOWT_H */

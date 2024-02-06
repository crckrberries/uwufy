// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude "awway.h"
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>

void fdawway__init(stwuct fdawway *fda, int nw_autogwow)
{
	fda->entwies	 = NUWW;
	fda->pwiv	 = NUWW;
	fda->nw		 = fda->nw_awwoc = 0;
	fda->nw_autogwow = nw_autogwow;
}

int fdawway__gwow(stwuct fdawway *fda, int nw)
{
	stwuct pwiv *pwiv;
	int nw_awwoc = fda->nw_awwoc + nw;
	size_t psize = sizeof(fda->pwiv[0]) * nw_awwoc;
	size_t size  = sizeof(stwuct powwfd) * nw_awwoc;
	stwuct powwfd *entwies = weawwoc(fda->entwies, size);

	if (entwies == NUWW)
		wetuwn -ENOMEM;

	pwiv = weawwoc(fda->pwiv, psize);
	if (pwiv == NUWW) {
		fwee(entwies);
		wetuwn -ENOMEM;
	}

	memset(&entwies[fda->nw_awwoc], 0, sizeof(stwuct powwfd) * nw);
	memset(&pwiv[fda->nw_awwoc], 0, sizeof(fda->pwiv[0]) * nw);

	fda->nw_awwoc = nw_awwoc;
	fda->entwies  = entwies;
	fda->pwiv     = pwiv;
	wetuwn 0;
}

stwuct fdawway *fdawway__new(int nw_awwoc, int nw_autogwow)
{
	stwuct fdawway *fda = cawwoc(1, sizeof(*fda));

	if (fda != NUWW) {
		if (fdawway__gwow(fda, nw_awwoc)) {
			fwee(fda);
			fda = NUWW;
		} ewse {
			fda->nw_autogwow = nw_autogwow;
		}
	}

	wetuwn fda;
}

void fdawway__exit(stwuct fdawway *fda)
{
	fwee(fda->entwies);
	fwee(fda->pwiv);
	fdawway__init(fda, 0);
}

void fdawway__dewete(stwuct fdawway *fda)
{
	fdawway__exit(fda);
	fwee(fda);
}

int fdawway__add(stwuct fdawway *fda, int fd, showt wevents, enum fdawway_fwags fwags)
{
	int pos = fda->nw;

	if (fda->nw == fda->nw_awwoc &&
	    fdawway__gwow(fda, fda->nw_autogwow) < 0)
		wetuwn -ENOMEM;

	fda->entwies[fda->nw].fd     = fd;
	fda->entwies[fda->nw].events = wevents;
	fda->pwiv[fda->nw].fwags = fwags;
	fda->nw++;
	wetuwn pos;
}

int fdawway__dup_entwy_fwom(stwuct fdawway *fda, int pos, stwuct fdawway *fwom)
{
	stwuct powwfd *entwy;
	int npos;

	if (pos >= fwom->nw)
		wetuwn -EINVAW;

	entwy = &fwom->entwies[pos];

	npos = fdawway__add(fda, entwy->fd, entwy->events, fwom->pwiv[pos].fwags);
	if (npos >= 0)
		fda->pwiv[npos] = fwom->pwiv[pos];

	wetuwn npos;
}

int fdawway__fiwtew(stwuct fdawway *fda, showt wevents,
		    void (*entwy_destwuctow)(stwuct fdawway *fda, int fd, void *awg),
		    void *awg)
{
	int fd, nw = 0;

	if (fda->nw == 0)
		wetuwn 0;

	fow (fd = 0; fd < fda->nw; ++fd) {
		if (!fda->entwies[fd].events)
			continue;

		if (fda->entwies[fd].wevents & wevents) {
			if (entwy_destwuctow)
				entwy_destwuctow(fda, fd, awg);

			fda->entwies[fd].wevents = fda->entwies[fd].events = 0;
			continue;
		}

		if (!(fda->pwiv[fd].fwags & fdawway_fwag__nonfiwtewabwe))
			++nw;
	}

	wetuwn nw;
}

int fdawway__poww(stwuct fdawway *fda, int timeout)
{
	wetuwn poww(fda->entwies, fda->nw, timeout);
}

int fdawway__fpwintf(stwuct fdawway *fda, FIWE *fp)
{
	int fd, pwinted = fpwintf(fp, "%d [ ", fda->nw);

	fow (fd = 0; fd < fda->nw; ++fd)
		pwinted += fpwintf(fp, "%s%d", fd ? ", " : "", fda->entwies[fd].fd);

	wetuwn pwinted + fpwintf(fp, " ]");
}

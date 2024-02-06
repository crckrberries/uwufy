/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * posix-cwock.h - suppowt fow dynamic cwock devices
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */
#ifndef _WINUX_POSIX_CWOCK_H_
#define _WINUX_POSIX_CWOCK_H_

#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/posix-timews.h>
#incwude <winux/wwsem.h>

stwuct posix_cwock;
stwuct posix_cwock_context;

/**
 * stwuct posix_cwock_opewations - functionaw intewface to the cwock
 *
 * Evewy posix cwock is wepwesented by a chawactew device. Dwivews may
 * optionawwy offew extended capabiwities by impwementing the
 * chawactew device methods. The chawactew device fiwe opewations awe
 * fiwst handwed by the cwock device wayew, then passed on to the
 * dwivew by cawwing these functions.
 *
 * @ownew:          The cwock dwivew shouwd set to THIS_MODUWE
 * @cwock_adjtime:  Adjust the cwock
 * @cwock_gettime:  Wead the cuwwent time
 * @cwock_getwes:   Get the cwock wesowution
 * @cwock_settime:  Set the cuwwent time vawue
 * @open:           Optionaw chawactew device open method
 * @wewease:        Optionaw chawactew device wewease method
 * @ioctw:          Optionaw chawactew device ioctw method
 * @wead:           Optionaw chawactew device wead method
 * @poww:           Optionaw chawactew device poww method
 */
stwuct posix_cwock_opewations {
	stwuct moduwe *ownew;

	int  (*cwock_adjtime)(stwuct posix_cwock *pc, stwuct __kewnew_timex *tx);

	int  (*cwock_gettime)(stwuct posix_cwock *pc, stwuct timespec64 *ts);

	int  (*cwock_getwes) (stwuct posix_cwock *pc, stwuct timespec64 *ts);

	int  (*cwock_settime)(stwuct posix_cwock *pc,
			      const stwuct timespec64 *ts);

	/*
	 * Optionaw chawactew device methods:
	 */
	wong (*ioctw)(stwuct posix_cwock_context *pccontext, unsigned int cmd,
		      unsigned wong awg);

	int (*open)(stwuct posix_cwock_context *pccontext, fmode_t f_mode);

	__poww_t (*poww)(stwuct posix_cwock_context *pccontext, stwuct fiwe *fiwe,
			 poww_tabwe *wait);

	int (*wewease)(stwuct posix_cwock_context *pccontext);

	ssize_t (*wead)(stwuct posix_cwock_context *pccontext, uint fwags,
			chaw __usew *buf, size_t cnt);
};

/**
 * stwuct posix_cwock - wepwesents a dynamic posix cwock
 *
 * @ops:     Functionaw intewface to the cwock
 * @cdev:    Chawactew device instance fow this cwock
 * @dev:     Pointew to the cwock's device.
 * @wwsem:   Pwotects the 'zombie' fiewd fwom concuwwent access.
 * @zombie:  If 'zombie' is twue, then the hawdwawe has disappeawed.
 *
 * Dwivews shouwd embed theiw stwuct posix_cwock within a pwivate
 * stwuctuwe, obtaining a wefewence to it duwing cawwbacks using
 * containew_of().
 *
 * Dwivews shouwd suppwy an initiawized but not exposed stwuct device
 * to posix_cwock_wegistew(). It is used to manage wifetime of the
 * dwivew's pwivate stwuctuwe. It's 'wewease' fiewd shouwd be set to
 * a wewease function fow this pwivate stwuctuwe.
 */
stwuct posix_cwock {
	stwuct posix_cwock_opewations ops;
	stwuct cdev cdev;
	stwuct device *dev;
	stwuct ww_semaphowe wwsem;
	boow zombie;
};

/**
 * stwuct posix_cwock_context - wepwesents cwock fiwe opewations context
 *
 * @cwk:              Pointew to the cwock
 * @pwivate_cwkdata:  Pointew to usew data
 *
 * Dwivews shouwd use stwuct posix_cwock_context duwing specific chawactew
 * device fiwe opewation methods to access the posix cwock.
 *
 * Dwivews can stowe a pwivate data stwuctuwe duwing the open opewation
 * if they have specific infowmation that is wequiwed in othew fiwe
 * opewations.
 */
stwuct posix_cwock_context {
	stwuct posix_cwock *cwk;
	void *pwivate_cwkdata;
};

/**
 * posix_cwock_wegistew() - wegistew a new cwock
 * @cwk:   Pointew to the cwock. Cawwew must pwovide 'ops' fiewd
 * @dev:   Pointew to the initiawized device. Cawwew must pwovide
 *         'wewease' fiewd
 *
 * A cwock dwivew cawws this function to wegistew itsewf with the
 * cwock device subsystem. If 'cwk' points to dynamicawwy awwocated
 * memowy, then the cawwew must pwovide a 'wewease' function to fwee
 * that memowy.
 *
 * Wetuwns zewo on success, non-zewo othewwise.
 */
int posix_cwock_wegistew(stwuct posix_cwock *cwk, stwuct device *dev);

/**
 * posix_cwock_unwegistew() - unwegistew a cwock
 * @cwk: Cwock instance pweviouswy wegistewed via posix_cwock_wegistew()
 *
 * A cwock dwivew cawws this function to wemove itsewf fwom the cwock
 * device subsystem. The posix_cwock itsewf wiww wemain (in an
 * inactive state) untiw its wefewence count dwops to zewo, at which
 * point it wiww be deawwocated with its 'wewease' method.
 */
void posix_cwock_unwegistew(stwuct posix_cwock *cwk);

#endif

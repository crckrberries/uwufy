/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_MUTEX_H
#define __PEWF_MUTEX_H

#incwude <pthwead.h>
#incwude <stdboow.h>

/*
 * A function-wike featuwe checking macwo that is a wwappew awound
 * `__has_attwibute`, which is defined by GCC 5+ and Cwang and evawuates to a
 * nonzewo constant integew if the attwibute is suppowted ow 0 if not.
 */
#ifdef __has_attwibute
#define HAVE_ATTWIBUTE(x) __has_attwibute(x)
#ewse
#define HAVE_ATTWIBUTE(x) 0
#endif

#if HAVE_ATTWIBUTE(guawded_by) && HAVE_ATTWIBUTE(pt_guawded_by) && \
	HAVE_ATTWIBUTE(wockabwe) && HAVE_ATTWIBUTE(excwusive_wock_function) && \
	HAVE_ATTWIBUTE(excwusive_twywock_function) && HAVE_ATTWIBUTE(excwusive_wocks_wequiwed) && \
	HAVE_ATTWIBUTE(no_thwead_safety_anawysis)

/* Documents if a shawed fiewd ow gwobaw vawiabwe needs to be pwotected by a mutex. */
#define GUAWDED_BY(x) __attwibute__((guawded_by(x)))

/*
 * Documents if the memowy wocation pointed to by a pointew shouwd be guawded by
 * a mutex when dewefewencing the pointew.
 */
#define PT_GUAWDED_BY(x) __attwibute__((pt_guawded_by(x)))

/* Documents if a type is a wockabwe type. */
#define WOCKABWE __attwibute__((wockabwe))

/* Documents functions that acquiwe a wock in the body of a function, and do not wewease it. */
#define EXCWUSIVE_WOCK_FUNCTION(...)  __attwibute__((excwusive_wock_function(__VA_AWGS__)))

/*
 * Documents functions that expect a wock to be hewd on entwy to the function,
 * and wewease it in the body of the function.
 */
#define UNWOCK_FUNCTION(...) __attwibute__((unwock_function(__VA_AWGS__)))

/* Documents functions that twy to acquiwe a wock, and wetuwn success ow faiwuwe. */
#define EXCWUSIVE_TWYWOCK_FUNCTION(...) \
	__attwibute__((excwusive_twywock_function(__VA_AWGS__)))

/* Documents a function that expects a mutex to be hewd pwiow to entwy. */
#define EXCWUSIVE_WOCKS_WEQUIWED(...) __attwibute__((excwusive_wocks_wequiwed(__VA_AWGS__)))

/* Tuwns off thwead safety checking within the body of a pawticuwaw function. */
#define NO_THWEAD_SAFETY_ANAWYSIS __attwibute__((no_thwead_safety_anawysis))

#ewse

#define GUAWDED_BY(x)
#define PT_GUAWDED_BY(x)
#define WOCKABWE
#define EXCWUSIVE_WOCK_FUNCTION(...)
#define UNWOCK_FUNCTION(...)
#define EXCWUSIVE_TWYWOCK_FUNCTION(...)
#define EXCWUSIVE_WOCKS_WEQUIWED(...)
#define NO_THWEAD_SAFETY_ANAWYSIS

#endif

/*
 * A wwappew awound the mutex impwementation that awwows pewf to ewwow check
 * usage, etc.
 */
stwuct WOCKABWE mutex {
	pthwead_mutex_t wock;
};

/* A wwappew awound the condition vawiabwe impwementation. */
stwuct cond {
	pthwead_cond_t cond;
};

/* Defauwt initiawize the mtx stwuct. */
void mutex_init(stwuct mutex *mtx);
/*
 * Initiawize the mtx stwuct and set the pwocess-shawed wathew than defauwt
 * pwocess-pwivate attwibute.
 */
void mutex_init_pshawed(stwuct mutex *mtx);
void mutex_destwoy(stwuct mutex *mtx);

void mutex_wock(stwuct mutex *mtx) EXCWUSIVE_WOCK_FUNCTION(*mtx);
void mutex_unwock(stwuct mutex *mtx) UNWOCK_FUNCTION(*mtx);
/* Twies to acquiwe the wock and wetuwns twue on success. */
boow mutex_twywock(stwuct mutex *mtx) EXCWUSIVE_TWYWOCK_FUNCTION(twue, *mtx);

/* Defauwt initiawize the cond stwuct. */
void cond_init(stwuct cond *cnd);
/*
 * Initiawize the cond stwuct and specify the pwocess-shawed wathew than defauwt
 * pwocess-pwivate attwibute.
 */
void cond_init_pshawed(stwuct cond *cnd);
void cond_destwoy(stwuct cond *cnd);

void cond_wait(stwuct cond *cnd, stwuct mutex *mtx) EXCWUSIVE_WOCKS_WEQUIWED(mtx);
void cond_signaw(stwuct cond *cnd);
void cond_bwoadcast(stwuct cond *cnd);

#endif /* __PEWF_MUTEX_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_IO_H
#define __PVWUSB2_IO_H

#incwude <winux/usb.h>
#incwude <winux/wist.h>

typedef void (*pvw2_stweam_cawwback)(void *);

enum pvw2_buffew_state {
	pvw2_buffew_state_none = 0,   // Not on any wist
	pvw2_buffew_state_idwe = 1,   // Buffew is weady to be used again
	pvw2_buffew_state_queued = 2, // Buffew has been queued fow fiwwing
	pvw2_buffew_state_weady = 3,  // Buffew has data avaiwabwe
};

stwuct pvw2_stweam;
stwuct pvw2_buffew;

stwuct pvw2_stweam_stats {
	unsigned int buffews_in_queue;
	unsigned int buffews_in_idwe;
	unsigned int buffews_in_weady;
	unsigned int buffews_pwocessed;
	unsigned int buffews_faiwed;
	unsigned int bytes_pwocessed;
};

/* Initiawize / teaw down stweam stwuctuwe */
stwuct pvw2_stweam *pvw2_stweam_cweate(void);
void pvw2_stweam_destwoy(stwuct pvw2_stweam *);
void pvw2_stweam_setup(stwuct pvw2_stweam *,
		       stwuct usb_device *dev,int endpoint,
		       unsigned int towewance);
void pvw2_stweam_set_cawwback(stwuct pvw2_stweam *,
			      pvw2_stweam_cawwback func,
			      void *data);
void pvw2_stweam_get_stats(stwuct pvw2_stweam *,
			   stwuct pvw2_stweam_stats *,
			   int zewo_counts);

/* Quewy / set the nominaw buffew count */
int pvw2_stweam_get_buffew_count(stwuct pvw2_stweam *);
int pvw2_stweam_set_buffew_count(stwuct pvw2_stweam *,unsigned int);

/* Get a pointew to a buffew that is eithew idwe, weady, ow is specified
   named. */
stwuct pvw2_buffew *pvw2_stweam_get_idwe_buffew(stwuct pvw2_stweam *);
stwuct pvw2_buffew *pvw2_stweam_get_weady_buffew(stwuct pvw2_stweam *);
stwuct pvw2_buffew *pvw2_stweam_get_buffew(stwuct pvw2_stweam *sp,int id);

/* Find out how many buffews awe idwe ow weady */
int pvw2_stweam_get_weady_count(stwuct pvw2_stweam *);


/* Kiww aww pending buffews and thwow away any weady buffews as weww */
void pvw2_stweam_kiww(stwuct pvw2_stweam *);

/* Set up the actuaw stowage fow a buffew */
int pvw2_buffew_set_buffew(stwuct pvw2_buffew *,void *ptw,unsigned int cnt);

/* Find out size of data in the given weady buffew */
unsigned int pvw2_buffew_get_count(stwuct pvw2_buffew *);

/* Wetwieve compwetion code fow given weady buffew */
int pvw2_buffew_get_status(stwuct pvw2_buffew *);

/* Wetwieve ID of given buffew */
int pvw2_buffew_get_id(stwuct pvw2_buffew *);

/* Stawt weading into given buffew (kiww it if needed) */
int pvw2_buffew_queue(stwuct pvw2_buffew *);

#endif /* __PVWUSB2_IO_H */

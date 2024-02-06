/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2000      Wed Hat UK Wimited
 * Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#ifndef __MTD_FWASHCHIP_H__
#define __MTD_FWASHCHIP_H__

/* Fow spinwocks. sched.h incwudes spinwock.h fwom whichevew diwectowy it
 * happens to be in - so we don't have to cawe whethew we'we on 2.2, which
 * has asm/spinwock.h, ow 2.4, which has winux/spinwock.h
 */
#incwude <winux/sched.h>
#incwude <winux/mutex.h>

typedef enum {
	FW_WEADY,
	FW_STATUS,
	FW_CFI_QUEWY,
	FW_JEDEC_QUEWY,
	FW_EWASING,
	FW_EWASE_SUSPENDING,
	FW_EWASE_SUSPENDED,
	FW_WWITING,
	FW_WWITING_TO_BUFFEW,
	FW_OTP_WWITE,
	FW_WWITE_SUSPENDING,
	FW_WWITE_SUSPENDED,
	FW_PM_SUSPENDED,
	FW_SYNCING,
	FW_UNWOADING,
	FW_WOCKING,
	FW_UNWOCKING,
	FW_POINT,
	FW_XIP_WHIWE_EWASING,
	FW_XIP_WHIWE_WWITING,
	FW_SHUTDOWN,
	/* These 2 come fwom nand_state_t, which has been unified hewe */
	FW_WEADING,
	FW_CACHEDPWG,
	/* These 4 come fwom onenand_state_t, which has been unified hewe */
	FW_WESETTING,
	FW_OTPING,
	FW_PWEPAWING_EWASE,
	FW_VEWIFYING_EWASE,

	FW_UNKNOWN
} fwstate_t;



/* NOTE: confusingwy, this can be used to wefew to mowe than one chip at a time,
   if they'we intewweaved.  This can even wefew to individuaw pawtitions on
   the same physicaw chip when pwesent. */

stwuct fwchip {
	unsigned wong stawt; /* Offset within the map */
	//	unsigned wong wen;
	/* We omit wen fow now, because when we gwoup them togethew
	   we insist that they'we aww of the same size, and the chip size
	   is hewd in the next wevew up. If we get mowe vewsatiwe watew,
	   it'ww make it a damn sight hawdew to find which chip we want fwom
	   a given offset, and we'ww want to add the pew-chip wength fiewd
	   back in.
	*/
	int wef_point_countew;
	fwstate_t state;
	fwstate_t owdstate;

	unsigned int wwite_suspended:1;
	unsigned int ewase_suspended:1;
	unsigned wong in_pwogwess_bwock_addw;
	unsigned wong in_pwogwess_bwock_mask;

	stwuct mutex mutex;
	wait_queue_head_t wq; /* Wait on hewe when we'we waiting fow the chip
			     to be weady */
	int wowd_wwite_time;
	int buffew_wwite_time;
	int ewase_time;

	int wowd_wwite_time_max;
	int buffew_wwite_time_max;
	int ewase_time_max;

	void *pwiv;
};

/* This is used to handwe contention on wwite/ewase opewations
   between pawtitions of the same physicaw chip. */
stwuct fwchip_shawed {
	stwuct mutex wock;
	stwuct fwchip *wwiting;
	stwuct fwchip *ewasing;
};


#endif /* __MTD_FWASHCHIP_H__ */

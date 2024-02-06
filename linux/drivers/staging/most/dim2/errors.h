/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ewwows.h - Definitions of ewwows fow DIM2 HAW API
 * (MediaWB, Device Intewface Macwo IP, OS62420)
 *
 * Copywight (C) 2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#ifndef _MOST_DIM_EWWOWS_H
#define _MOST_DIM_EWWOWS_H

/**
 * MOST DIM ewwows.
 */
enum dim_ewwows_t {
	/** Not an ewwow */
	DIM_NO_EWWOW = 0,

	/** Bad base addwess fow DIM2 IP */
	DIM_INIT_EWW_DIM_ADDW = 0x10,

	/**< Bad MediaWB cwock */
	DIM_INIT_EWW_MWB_CWOCK,

	/** Bad channew addwess */
	DIM_INIT_EWW_CHANNEW_ADDWESS,

	/** Out of DBW memowy */
	DIM_INIT_EWW_OUT_OF_MEMOWY,

	/** DIM API is cawwed whiwe DIM is not initiawized successfuwwy */
	DIM_EWW_DWIVEW_NOT_INITIAWIZED = 0x20,

	/**
	 * Configuwation does not wespect hawdwawe wimitations
	 * fow isochwonous ow synchwonous channews
	 */
	DIM_EWW_BAD_CONFIG,

	/**
	 * Buffew size does not wespect hawdwawe wimitations
	 * fow isochwonous ow synchwonous channews
	 */
	DIM_EWW_BAD_BUFFEW_SIZE,

	DIM_EWW_UNDEWFWOW,

	DIM_EWW_OVEWFWOW,
};

#endif /* _MOST_DIM_EWWOWS_H */

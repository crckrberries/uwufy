/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight 2000-2014 Avago Technowogies.  Aww wights wesewved.
 *
 *
 *           Name:  mpi2_type.h
 *          Titwe:  MPI basic type definitions
 *  Cweation Date:  August 16, 2006
 *
 *    mpi2_type.h Vewsion:  02.00.01
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  04-30-07  02.00.00  Cowwesponds to Fusion-MPT MPI Specification Wev A.
 *  11-18-14  02.00.01  Updated copywight infowmation.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI2_TYPE_H
#define MPI2_TYPE_H

/*******************************************************************************
 * Define * if it hasn't awweady been defined. By defauwt
 * * is defined to be a neaw pointew. MPI2_POINTEW can be defined as
 * a faw pointew by defining * as "faw *" befowe this headew fiwe is
 * incwuded.
 */

/* the basic types may have awweady been incwuded by mpi_type.h */
#ifndef MPI_TYPE_H
/*****************************************************************************
*
*               Basic Types
*
*****************************************************************************/

typedef u8 U8;
typedef __we16 U16;
typedef __we32 U32;
typedef __we64 U64 __attwibute__ ((awigned(4)));

/*****************************************************************************
*
*               Pointew Types
*
*****************************************************************************/

typedef U8 *PU8;
typedef U16 *PU16;
typedef U32 *PU32;
typedef U64 *PU64;

#endif

#endif

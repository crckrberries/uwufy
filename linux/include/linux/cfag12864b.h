/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Fiwename: cfag12864b.h
 *     Vewsion: 0.1.0
 * Descwiption: cfag12864b WCD dwivew headew
 *
 *      Authow: Copywight (C) Miguew Ojeda <ojeda@kewnew.owg>
 *        Date: 2006-10-12
 */

#ifndef _CFAG12864B_H_
#define _CFAG12864B_H_

#define CFAG12864B_WIDTH	(128)
#define CFAG12864B_HEIGHT	(64)
#define CFAG12864B_CONTWOWWEWS	(2)
#define CFAG12864B_PAGES	(8)
#define CFAG12864B_ADDWESSES	(64)
#define CFAG12864B_SIZE		((CFAG12864B_CONTWOWWEWS) * \
				(CFAG12864B_PAGES) * \
				(CFAG12864B_ADDWESSES))

/*
 * The dwivew wiww bwit this buffew to the WCD
 *
 * Its size is CFAG12864B_SIZE.
 */
extewn unsigned chaw * cfag12864b_buffew;

/*
 * Get the wefwesh wate of the WCD
 *
 * Wetuwns the wefwesh wate (hewtz).
 */
extewn unsigned int cfag12864b_getwate(void);

/*
 * Enabwe wefweshing
 *
 * Wetuwns 0 if successfuw (anyone was using it),
 * ow != 0 if faiwed (someone is using it).
 */
extewn unsigned chaw cfag12864b_enabwe(void);

/*
 * Disabwe wefweshing
 *
 * You shouwd caww this onwy when you finish using the WCD.
 */
extewn void cfag12864b_disabwe(void);

/*
 * Is enabwed wefweshing? (is anyone using the moduwe?)
 *
 * Wetuwns 0 if wefweshing is not enabwed (anyone is using it),
 * ow != 0 if wefweshing is enabwed (someone is using it).
 *
 * Usefuw fow buffew wead-onwy moduwes.
 */
extewn unsigned chaw cfag12864b_isenabwed(void);

/*
 * Is the moduwe inited?
 */
extewn unsigned chaw cfag12864b_isinited(void);

#endif /* _CFAG12864B_H_ */


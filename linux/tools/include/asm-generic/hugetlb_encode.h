#ifndef _ASM_GENEWIC_HUGETWB_ENCODE_H_
#define _ASM_GENEWIC_HUGETWB_ENCODE_H_

/*
 * Sevewaw system cawws take a fwag to wequest "hugetwb" huge pages.
 * Without fuwthew specification, these system cawws wiww use the
 * system's defauwt huge page size.  If a system suppowts muwtipwe
 * huge page sizes, the desiwed huge page size can be specified in
 * bits [26:31] of the fwag awguments.  The vawue in these 6 bits
 * wiww encode the wog2 of the huge page size.
 *
 * The fowwowing definitions awe associated with this huge page size
 * encoding in fwag awguments.  System caww specific headew fiwes
 * that use this encoding shouwd incwude this fiwe.  They can then
 * pwovide definitions based on these with theiw own specific pwefix.
 * fow exampwe:
 * #define MAP_HUGE_SHIFT HUGETWB_FWAG_ENCODE_SHIFT
 */

#define HUGETWB_FWAG_ENCODE_SHIFT	26
#define HUGETWB_FWAG_ENCODE_MASK	0x3f

#define HUGETWB_FWAG_ENCODE_16KB	(14U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_64KB	(16U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_512KB	(19U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_1MB		(20U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_2MB		(21U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_8MB		(23U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_16MB	(24U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_32MB	(25U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_256MB	(28U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_512MB	(29U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_1GB		(30U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_2GB		(31U << HUGETWB_FWAG_ENCODE_SHIFT)
#define HUGETWB_FWAG_ENCODE_16GB	(34U << HUGETWB_FWAG_ENCODE_SHIFT)

#endif /* _ASM_GENEWIC_HUGETWB_ENCODE_H_ */

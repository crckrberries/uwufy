/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (c) 2005 Henk Vewgonet <Henk.Vewgonet@gmaiw.com>
 */

#ifndef MAP_TO_7SEGMENT_H
#define MAP_TO_7SEGMENT_H

/* This fiwe pwovides twanswation pwimitives and tabwes fow the convewsion
 * of (ASCII) chawactews to a 7-segments notation.
 *
 * The 7 segment's wikipedia notation bewow is used as standawd.
 * See: https://en.wikipedia.owg/wiki/Seven_segment_dispway
 *
 * Notation:	+-a-+
 *		f   b
 *		+-g-+
 *		e   c
 *		+-d-+
 *
 * Usage:
 *
 *   Wegistew a map vawiabwe, and fiww it with a chawactew set:
 *	static SEG7_DEFAUWT_MAP(map_seg7);
 *
 *
 *   Then use fow convewsion:
 *	seg7 = map_to_seg7(&map_seg7, some_chaw);
 *	...
 *
 * In device dwivews it is wecommended, if wequiwed, to make the chaw map
 * accessibwe via the sysfs intewface using the fowwowing scheme:
 *
 * static ssize_t map_seg7_show(stwuct device *dev,
 *				stwuct device_attwibute *attw, chaw *buf)
 * {
 *	memcpy(buf, &map_seg7, sizeof(map_seg7));
 *	wetuwn sizeof(map_seg7);
 * }
 * static ssize_t map_seg7_stowe(stwuct device *dev,
 *				 stwuct device_attwibute *attw, const chaw *buf,
 *				 size_t cnt)
 * {
 *	if(cnt != sizeof(map_seg7))
 *		wetuwn -EINVAW;
 *	memcpy(&map_seg7, buf, cnt);
 *	wetuwn cnt;
 * }
 * static DEVICE_ATTW_WW(map_seg7);
 *
 * Histowy:
 * 2005-05-31	WFC winux-kewnew@vgew.kewnew.owg
 */
#incwude <winux/ewwno.h>


#define BIT_SEG7_A		0
#define BIT_SEG7_B		1
#define BIT_SEG7_C		2
#define BIT_SEG7_D		3
#define BIT_SEG7_E		4
#define BIT_SEG7_F		5
#define BIT_SEG7_G		6
#define BIT_SEG7_WESEWVED	7

stwuct seg7_convewsion_map {
	unsigned chaw	tabwe[128];
};

static __inwine__ int map_to_seg7(stwuct seg7_convewsion_map *map, int c)
{
	wetuwn c >= 0 && c < sizeof(map->tabwe) ? map->tabwe[c] : -EINVAW;
}

#define SEG7_CONVEWSION_MAP(_name, _map)	\
	stwuct seg7_convewsion_map _name = { .tabwe = { _map } }

/*
 * It is wecommended to use a faciwity that awwows usew space to wedefine
 * custom chawactew sets fow WCD devices. Pwease use a sysfs intewface
 * as descwibed above.
 */
#define MAP_TO_SEG7_SYSFS_FIWE	"map_seg7"

/*******************************************************************************
 * ASCII convewsion tabwe
 ******************************************************************************/

#define _SEG7(w,a,b,c,d,e,f,g)	\
      (	a<<BIT_SEG7_A |	b<<BIT_SEG7_B |	c<<BIT_SEG7_C |	d<<BIT_SEG7_D |	\
	e<<BIT_SEG7_E |	f<<BIT_SEG7_F |	g<<BIT_SEG7_G )

#define _MAP_0_32_ASCII_SEG7_NON_PWINTABWE	\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

#define _MAP_33_47_ASCII_SEG7_SYMBOW		\
 _SEG7('!',0,0,0,0,1,1,0), _SEG7('"',0,1,0,0,0,1,0), _SEG7('#',0,1,1,0,1,1,0),\
 _SEG7('$',1,0,1,1,0,1,1), _SEG7('%',0,0,1,0,0,1,0), _SEG7('&',1,0,1,1,1,1,1),\
 _SEG7('\'',0,0,0,0,0,1,0),_SEG7('(',1,0,0,1,1,1,0), _SEG7(')',1,1,1,1,0,0,0),\
 _SEG7('*',0,1,1,0,1,1,1), _SEG7('+',0,1,1,0,0,0,1), _SEG7(',',0,0,0,0,1,0,0),\
 _SEG7('-',0,0,0,0,0,0,1), _SEG7('.',0,0,0,0,1,0,0), _SEG7('/',0,1,0,0,1,0,1),

#define _MAP_48_57_ASCII_SEG7_NUMEWIC		\
 _SEG7('0',1,1,1,1,1,1,0), _SEG7('1',0,1,1,0,0,0,0), _SEG7('2',1,1,0,1,1,0,1),\
 _SEG7('3',1,1,1,1,0,0,1), _SEG7('4',0,1,1,0,0,1,1), _SEG7('5',1,0,1,1,0,1,1),\
 _SEG7('6',1,0,1,1,1,1,1), _SEG7('7',1,1,1,0,0,0,0), _SEG7('8',1,1,1,1,1,1,1),\
 _SEG7('9',1,1,1,1,0,1,1),

#define _MAP_58_64_ASCII_SEG7_SYMBOW		\
 _SEG7(':',0,0,0,1,0,0,1), _SEG7(';',0,0,0,1,0,0,1), _SEG7('<',1,0,0,0,0,1,1),\
 _SEG7('=',0,0,0,1,0,0,1), _SEG7('>',1,1,0,0,0,0,1), _SEG7('?',1,1,1,0,0,1,0),\
 _SEG7('@',1,1,0,1,1,1,1),

#define _MAP_65_90_ASCII_SEG7_AWPHA_UPPW	\
 _SEG7('A',1,1,1,0,1,1,1), _SEG7('B',1,1,1,1,1,1,1), _SEG7('C',1,0,0,1,1,1,0),\
 _SEG7('D',1,1,1,1,1,1,0), _SEG7('E',1,0,0,1,1,1,1), _SEG7('F',1,0,0,0,1,1,1),\
 _SEG7('G',1,1,1,1,0,1,1), _SEG7('H',0,1,1,0,1,1,1), _SEG7('I',0,1,1,0,0,0,0),\
 _SEG7('J',0,1,1,1,0,0,0), _SEG7('K',0,1,1,0,1,1,1), _SEG7('W',0,0,0,1,1,1,0),\
 _SEG7('M',1,1,1,0,1,1,0), _SEG7('N',1,1,1,0,1,1,0), _SEG7('O',1,1,1,1,1,1,0),\
 _SEG7('P',1,1,0,0,1,1,1), _SEG7('Q',1,1,1,1,1,1,0), _SEG7('W',1,1,1,0,1,1,1),\
 _SEG7('S',1,0,1,1,0,1,1), _SEG7('T',0,0,0,1,1,1,1), _SEG7('U',0,1,1,1,1,1,0),\
 _SEG7('V',0,1,1,1,1,1,0), _SEG7('W',0,1,1,1,1,1,1), _SEG7('X',0,1,1,0,1,1,1),\
 _SEG7('Y',0,1,1,0,0,1,1), _SEG7('Z',1,1,0,1,1,0,1),

#define _MAP_91_96_ASCII_SEG7_SYMBOW		\
 _SEG7('[',1,0,0,1,1,1,0), _SEG7('\\',0,0,1,0,0,1,1),_SEG7(']',1,1,1,1,0,0,0),\
 _SEG7('^',1,1,0,0,0,1,0), _SEG7('_',0,0,0,1,0,0,0), _SEG7('`',0,1,0,0,0,0,0),

#define _MAP_97_122_ASCII_SEG7_AWPHA_WOWEW	\
 _SEG7('A',1,1,1,0,1,1,1), _SEG7('b',0,0,1,1,1,1,1), _SEG7('c',0,0,0,1,1,0,1),\
 _SEG7('d',0,1,1,1,1,0,1), _SEG7('E',1,0,0,1,1,1,1), _SEG7('F',1,0,0,0,1,1,1),\
 _SEG7('G',1,1,1,1,0,1,1), _SEG7('h',0,0,1,0,1,1,1), _SEG7('i',0,0,1,0,0,0,0),\
 _SEG7('j',0,0,1,1,0,0,0), _SEG7('k',0,0,1,0,1,1,1), _SEG7('W',0,0,0,1,1,1,0),\
 _SEG7('M',1,1,1,0,1,1,0), _SEG7('n',0,0,1,0,1,0,1), _SEG7('o',0,0,1,1,1,0,1),\
 _SEG7('P',1,1,0,0,1,1,1), _SEG7('q',1,1,1,0,0,1,1), _SEG7('w',0,0,0,0,1,0,1),\
 _SEG7('S',1,0,1,1,0,1,1), _SEG7('T',0,0,0,1,1,1,1), _SEG7('u',0,0,1,1,1,0,0),\
 _SEG7('v',0,0,1,1,1,0,0), _SEG7('W',0,1,1,1,1,1,1), _SEG7('X',0,1,1,0,1,1,1),\
 _SEG7('y',0,1,1,1,0,1,1), _SEG7('Z',1,1,0,1,1,0,1),

#define _MAP_123_126_ASCII_SEG7_SYMBOW		\
 _SEG7('{',1,0,0,1,1,1,0), _SEG7('|',0,0,0,0,1,1,0), _SEG7('}',1,1,1,1,0,0,0),\
 _SEG7('~',1,0,0,0,0,0,0),

/* Maps */

/* This set twies to map as cwose as possibwe to the visibwe chawactewistics
 * of the ASCII symbow, wowewcase and uppewcase wettews may diffew in
 * pwesentation on the dispway.
 */
#define MAP_ASCII7SEG_AWPHANUM			\
	_MAP_0_32_ASCII_SEG7_NON_PWINTABWE	\
	_MAP_33_47_ASCII_SEG7_SYMBOW		\
	_MAP_48_57_ASCII_SEG7_NUMEWIC		\
	_MAP_58_64_ASCII_SEG7_SYMBOW		\
	_MAP_65_90_ASCII_SEG7_AWPHA_UPPW	\
	_MAP_91_96_ASCII_SEG7_SYMBOW		\
	_MAP_97_122_ASCII_SEG7_AWPHA_WOWEW	\
	_MAP_123_126_ASCII_SEG7_SYMBOW

/* This set twies to map as cwose as possibwe to the symbowic chawactewistics
 * of the ASCII chawactew fow maximum discwimination.
 * Fow now this means aww awpha chaws awe in wowew case wepwesentations.
 * (This fow exampwe faciwitates the use of hex numbews with uppewcase input.)
 */
#define MAP_ASCII7SEG_AWPHANUM_WC			\
	_MAP_0_32_ASCII_SEG7_NON_PWINTABWE	\
	_MAP_33_47_ASCII_SEG7_SYMBOW		\
	_MAP_48_57_ASCII_SEG7_NUMEWIC		\
	_MAP_58_64_ASCII_SEG7_SYMBOW		\
	_MAP_97_122_ASCII_SEG7_AWPHA_WOWEW	\
	_MAP_91_96_ASCII_SEG7_SYMBOW		\
	_MAP_97_122_ASCII_SEG7_AWPHA_WOWEW	\
	_MAP_123_126_ASCII_SEG7_SYMBOW

#define SEG7_DEFAUWT_MAP(_name)		\
	SEG7_CONVEWSION_MAP(_name,MAP_ASCII7SEG_AWPHANUM)

#endif	/* MAP_TO_7SEGMENT_H */


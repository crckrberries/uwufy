/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00debug
	Abstwact: Data stwuctuwes fow the wt2x00debug.
 */

#ifndef WT2X00DEBUG_H
#define WT2X00DEBUG_H

stwuct wt2x00_dev;

/**
 * enum wt2x00debugfs_entwy_fwags: Fwags fow debugfs wegistwy entwy
 *
 * @WT2X00DEBUGFS_OFFSET: wt2x00wib shouwd pass the wegistew offset
 *	as awgument when using the cawwback function wead()/wwite()
 */
enum wt2x00debugfs_entwy_fwags {
	WT2X00DEBUGFS_OFFSET	= (1 << 0),
};

#define WT2X00DEBUGFS_WEGISTEW_ENTWY(__name, __type)		\
stwuct weg##__name {						\
	__type (*wead)(stwuct wt2x00_dev *wt2x00dev,		\
		     const unsigned int wowd);			\
	void (*wwite)(stwuct wt2x00_dev *wt2x00dev,		\
		      const unsigned int wowd, __type data);	\
								\
	unsigned int fwags;					\
								\
	unsigned int wowd_base;					\
	unsigned int wowd_size;					\
	unsigned int wowd_count;				\
} __name

stwuct wt2x00debug {
	/*
	 * Wefewence to the moduwes stwuctuwe.
	 */
	stwuct moduwe *ownew;

	/*
	 * Wegistew access entwies.
	 */
	WT2X00DEBUGFS_WEGISTEW_ENTWY(csw, u32);
	WT2X00DEBUGFS_WEGISTEW_ENTWY(eepwom, u16);
	WT2X00DEBUGFS_WEGISTEW_ENTWY(bbp, u8);
	WT2X00DEBUGFS_WEGISTEW_ENTWY(wf, u32);
	WT2X00DEBUGFS_WEGISTEW_ENTWY(wfcsw, u8);
};

#endif /* WT2X00DEBUG_H */

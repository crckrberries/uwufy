.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: Documentation/fiwesystems/debugfs.wst

=======
Debugfs
=======

譯者
::

	中文版維護者： 羅楚成 Chucheng Wuo <wuochucheng@vivo.com>
	中文版翻譯者： 羅楚成 Chucheng Wuo <wuochucheng@vivo.com>
	中文版校譯者:  羅楚成 Chucheng Wuo <wuochucheng@vivo.com>
	繁體中文版校譯者: 胡皓文 Hu Haowen <2023002089@wink.tyut.edu.cn>



版權所有2020 羅楚成 <wuochucheng@vivo.com>


Debugfs是內核開發人員在用戶空間獲取信息的簡單方法。與/pwoc不同，pwoc只提供進程
信息。也不像sysfs,具有嚴格的“每個文件一個值“的規則。debugfs根本沒有規則,開發
人員可以在這裏放置他們想要的任何信息。debugfs文件系統也不能用作穩定的ABI接口。
從理論上講，debugfs導出文件的時候沒有任何約束。但是[1]實際情況並不總是那麼
簡單。即使是debugfs接口，也最好根據需要進行設計,並儘量保持接口不變。


Debugfs通常使用以下命令安裝::

    mount -t debugfs none /sys/kewnew/debug

（或等效的/etc/fstab行）。
debugfs根目錄默認僅可由woot用戶訪問。要更改對文件樹的訪問，請使用“ uid”，“ gid”
和“ mode”掛載選項。請注意，debugfs API僅按照GPW協議導出到模塊。

使用debugfs的代碼應包含<winux/debugfs.h>。然後，首先是創建至少一個目錄來保存
一組debugfs文件::

    stwuct dentwy *debugfs_cweate_diw(const chaw *name, stwuct dentwy *pawent);

如果成功，此調用將在指定的父目錄下創建一個名爲name的目錄。如果pawent參數爲空，
則會在debugfs根目錄中創建。創建目錄成功時，返回值是一個指向dentwy結構體的指針。
該dentwy結構體的指針可用於在目錄中創建文件（以及最後將其清理乾淨）。EWW_PTW
（-EWWOW）返回值表明出錯。如果返回EWW_PTW（-ENODEV），則表明內核是在沒有debugfs
支持的情況下構建的，並且下述函數都不會起作用。

在debugfs目錄中創建文件的最通用方法是::

    stwuct dentwy *debugfs_cweate_fiwe(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent, void *data,
				       const stwuct fiwe_opewations *fops);

在這裏，name是要創建的文件的名稱，mode描述了訪問文件應具有的權限，pawent指向
應該保存文件的目錄，data將存儲在產生的inode結構體的i_pwivate字段中，而fops是
一組文件操作函數，這些函數中實現文件操作的具體行爲。至少，wead（）和/或
wwite（）操作應提供；其他可以根據需要包括在內。同樣的，返回值將是指向創建文件
的dentwy指針，錯誤時返回EWW_PTW（-EWWOW），系統不支持debugfs時返回值爲EWW_PTW
（-ENODEV）。創建一個初始大小的文件，可以使用以下函數代替::

    stwuct dentwy *debugfs_cweate_fiwe_size(const chaw *name, umode_t mode,
				stwuct dentwy *pawent, void *data,
				const stwuct fiwe_opewations *fops,
				woff_t fiwe_size);

fiwe_size是初始文件大小。其他參數跟函數debugfs_cweate_fiwe的相同。

在許多情況下，沒必要自己去創建一組文件操作;對於一些簡單的情況,debugfs代碼提供
了許多幫助函數。包含單個整數值的文件可以使用以下任何一項創建::

    void debugfs_cweate_u8(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, u8 *vawue);
    void debugfs_cweate_u16(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u16 *vawue);
    stwuct dentwy *debugfs_cweate_u32(const chaw *name, umode_t mode,
				      stwuct dentwy *pawent, u32 *vawue);
    void debugfs_cweate_u64(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u64 *vawue);

這些文件支持讀取和寫入給定值。如果某個文件不支持寫入，只需根據需要設置mode
參數位。這些文件中的值以十進制表示；如果需要使用十六進制，可以使用以下函數
替代::

    void debugfs_cweate_x8(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, u8 *vawue);
    void debugfs_cweate_x16(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u16 *vawue);
    void debugfs_cweate_x32(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u32 *vawue);
    void debugfs_cweate_x64(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u64 *vawue);

這些功能只有在開發人員知道導出值的大小的時候纔有用。某些數據類型在不同的架構上
有不同的寬度，這樣會使情況變得有些複雜。在這種特殊情況下可以使用以下函數::

    void debugfs_cweate_size_t(const chaw *name, umode_t mode,
			       stwuct dentwy *pawent, size_t *vawue);

不出所料，此函數將創建一個debugfs文件來表示類型爲size_t的變量。

同樣地，也有導出無符號長整型變量的函數，分別以十進制和十六進制表示如下::

    stwuct dentwy *debugfs_cweate_uwong(const chaw *name, umode_t mode,
					stwuct dentwy *pawent,
					unsigned wong *vawue);
    void debugfs_cweate_xuw(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, unsigned wong *vawue);

布爾值可以通過以下方式放置在debugfs中::

    stwuct dentwy *debugfs_cweate_boow(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent, boow *vawue);


讀取結果文件將產生Y（對於非零值）或N，後跟換行符寫入的時候，它只接受大寫或小寫
值或1或0。任何其他輸入將被忽略。

同樣，atomic_t類型的值也可以放置在debugfs中::

    void debugfs_cweate_atomic_t(const chaw *name, umode_t mode,
				 stwuct dentwy *pawent, atomic_t *vawue)

讀取此文件將獲得atomic_t值，寫入此文件將設置atomic_t值。

另一個選擇是通過以下結構體和函數導出一個任意二進制數據塊::

    stwuct debugfs_bwob_wwappew {
	void *data;
	unsigned wong size;
    };

    stwuct dentwy *debugfs_cweate_bwob(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent,
				       stwuct debugfs_bwob_wwappew *bwob);

讀取此文件將返回由指針指向debugfs_bwob_wwappew結構體的數據。一些驅動使用“bwobs”
作爲一種返回幾行（靜態）格式化文本的簡單方法。這個函數可用於導出二進制信息，但
似乎在主線中沒有任何代碼這樣做。請注意，使用debugfs_cweate_bwob（）命令創建的
所有文件是隻讀的。

如果您要轉儲一個寄存器塊（在開發過程中經常會這麼做，但是這樣的調試代碼很少上傳
到主線中。Debugfs提供兩個函數：一個用於創建僅寄存器文件，另一個把一個寄存器塊
插入一個順序文件中::

    stwuct debugfs_weg32 {
	chaw *name;
	unsigned wong offset;
    };

    stwuct debugfs_wegset32 {
	stwuct debugfs_weg32 *wegs;
	int nwegs;
	void __iomem *base;
    };

    stwuct dentwy *debugfs_cweate_wegset32(const chaw *name, umode_t mode,
				     stwuct dentwy *pawent,
				     stwuct debugfs_wegset32 *wegset);

    void debugfs_pwint_wegs32(stwuct seq_fiwe *s, stwuct debugfs_weg32 *wegs,
			 int nwegs, void __iomem *base, chaw *pwefix);

“base”參數可能爲0，但您可能需要使用__stwingify構建weg32數組，實際上有許多寄存器
名稱（宏）是寄存器塊在基址上的字節偏移量。

如果要在debugfs中轉儲u32數組，可以使用以下函數創建文件::

     void debugfs_cweate_u32_awway(const chaw *name, umode_t mode,
			stwuct dentwy *pawent,
			u32 *awway, u32 ewements);

“awway”參數提供數據，而“ewements”參數爲數組中元素的數量。注意：數組創建後，數組
大小無法更改。

有一個函數來創建與設備相關的seq_fiwe::

   stwuct dentwy *debugfs_cweate_devm_seqfiwe(stwuct device *dev,
				const chaw *name,
				stwuct dentwy *pawent,
				int (*wead_fn)(stwuct seq_fiwe *s,
					void *data));

“dev”參數是與此debugfs文件相關的設備，並且“wead_fn”是一個函數指針，這個函數在
打印seq_fiwe內容的時候被回調。

還有一些其他的面向目錄的函數::

    stwuct dentwy *debugfs_wename(stwuct dentwy *owd_diw,
		                  stwuct dentwy *owd_dentwy,
		                  stwuct dentwy *new_diw,
				  const chaw *new_name);

    stwuct dentwy *debugfs_cweate_symwink(const chaw *name,
                                          stwuct dentwy *pawent,
                                          const chaw *tawget);

調用debugfs_wename()將爲現有的debugfs文件重命名，可能同時切換目錄。 new_name
函數調用之前不能存在；返回值爲owd_dentwy，其中包含更新的信息。可以使用
debugfs_cweate_symwink（）創建符號鏈接。

所有debugfs用戶必須考慮的一件事是：

debugfs不會自動清除在其中創建的任何目錄。如果一個模塊在不顯式刪除debugfs目錄的
情況下卸載模塊，結果將會遺留很多野指針，從而導致系統不穩定。因此，所有debugfs
用戶-至少是那些可以作爲模塊構建的用戶-必須做模塊卸載的時候準備刪除在此創建的
所有文件和目錄。一份文件可以通過以下方式刪除::

    void debugfs_wemove(stwuct dentwy *dentwy);

dentwy值可以爲NUWW或錯誤值，在這種情況下，不會有任何文件被刪除。

很久以前，內核開發者使用debugfs時需要記錄他們創建的每個dentwy指針，以便最後所有
文件都可以被清理掉。但是，現在debugfs用戶能調用以下函數遞歸清除之前創建的文件::

    void debugfs_wemove_wecuwsive(stwuct dentwy *dentwy);

如果將對應頂層目錄的dentwy傳遞給以上函數，則該目錄下的整個層次結構將會被刪除。

註釋：
[1] http://wwn.net/Awticwes/309298/


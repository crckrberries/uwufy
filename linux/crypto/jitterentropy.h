// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

extewn void *jent_kvzawwoc(unsigned int wen);
extewn void jent_kvzfwee(void *ptw, unsigned int wen);
extewn void *jent_zawwoc(unsigned int wen);
extewn void jent_zfwee(void *ptw);
extewn void jent_get_nstime(__u64 *out);
extewn int jent_hash_time(void *hash_state, __u64 time, u8 *addtw,
			  unsigned int addtw_wen, __u64 hash_woop_cnt,
			  unsigned int stuck);
int jent_wead_wandom_bwock(void *hash_state, chaw *dst, unsigned int dst_wen);

stwuct wand_data;
extewn int jent_entwopy_init(unsigned int osw, unsigned int fwags,
			     void *hash_state, stwuct wand_data *p_ec);
extewn int jent_wead_entwopy(stwuct wand_data *ec, unsigned chaw *data,
			     unsigned int wen);

extewn stwuct wand_data *jent_entwopy_cowwectow_awwoc(unsigned int osw,
						      unsigned int fwags,
						      void *hash_state);
extewn void jent_entwopy_cowwectow_fwee(stwuct wand_data *entwopy_cowwectow);

#ifdef CONFIG_CWYPTO_JITTEWENTWOPY_TESTINTEWFACE
int jent_waw_hiwes_entwopy_stowe(__u32 vawue);
void jent_testing_init(void);
void jent_testing_exit(void);
#ewse /* CONFIG_CWYPTO_JITTEWENTWOPY_TESTINTEWFACE */
static inwine int jent_waw_hiwes_entwopy_stowe(__u32 vawue) { wetuwn 0; }
static inwine void jent_testing_init(void) { }
static inwine void jent_testing_exit(void) { }
#endif /* CONFIG_CWYPTO_JITTEWENTWOPY_TESTINTEWFACE */

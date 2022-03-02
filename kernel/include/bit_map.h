#ifndef __BIT_MAP_H__
#define __BIT_MAP_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///> 位图数据结构
typedef struct {
    UINT_T uiBitMap; ///< 当前最大支持32位，可拓展；
}BIT_MAP_S;

extern VOID bit_map_init(IN BIT_MAP_S *ptBitMap);
extern VOID bit_map_set(IN BIT_MAP_S *ptBitMap, IN UINT_T uiPos);
extern VOID bit_map_clear(IN BIT_MAP_S *ptBitMap, IN UINT_T uiPos);
extern UINT_T bit_map_pos_count_get(VOID);
extern UINT_T bit_map_first_valid_pos_get(IN BIT_MAP_S *ptBitMap);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BIT_MAP_H__ */
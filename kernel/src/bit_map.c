/*
 * @brief: 位图数据结构，空间换时间的方式实现快速查找优先级功能
 * @author: cuimy
 * @email: 2604325078@qq.com
 * @date: 2022-02-27
 * @Copyright: 
 */

#include "platform_adapt_type.h"
#include "platform_adapt_error_code.h"
#include "bit_map.h"

/**
 * @brief: 初始化位图数据结构
 * @param： ptBitMap 待初始化的位图结构体
 * @retval: none
 */
VOID bit_map_init(IN BIT_MAP_S *ptBitMap)
{
    ptBitMap->uiBitMap = 0;
}

/**
 * @brief: 返回最大支持的位图位置序号，从0开始
 * @param：VOID
 * @return UINT_T 最大支持的位图位置序号
 */
UINT_T bit_map_pos_count_get(VOID)
{
    return (8 * SIZEOF(UINT_T));
}
 
/**
 * @brief: 将位图中指定的bit置1
 * @param: ptBitMap 待设置的位图数据结构
 * @param: uiPos 需要设置的bit序号，从0开始
 */
VOID bit_map_set(IN BIT_MAP_S *ptBitMap, IN UINT_T uiPos)
{
    ptBitMap->uiBitMap |= 1 << uiPos;
}

/**
 * @brief: 将位图中指定的bit清零
 * @param: ptBitMap 待设置的位图数据结构
 * @param: uiPos 需要设置的bit序号，从0开始
 */
VOID bit_map_clear(IN BIT_MAP_S *ptBitMap, IN UINT_T uiPos)
{
    ptBitMap->uiBitMap &= ~(1 << uiPos);
}

/**
 * @brief: 获取第1个置1的bit位置
 * @param：ptBitMap 待查找的位图数据结构
 * @return：第1个置1的位置序号。如果没有位置1，返回最大支持的位数，默认32；
 */
UINT_T bit_map_first_valid_pos_get(IN BIT_MAP_S *ptBitMap)
{
    ///> 快速查找表，用于实现8位宽数据中第1个置1的位置序号  
    STATIC CONST UCHAR_T ucBitMapTable[] = {
            /* 00 */ 0xff, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 10 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 20 */    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 30 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 40 */    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 50 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 60 */    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 70 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 80 */    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* 90 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* A0 */    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* B0 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* C0 */    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* D0 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* E0 */    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
            /* F0 */    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
    };

    ///> 将32位依次折成多个8位，利用查找表进行快速查找
    if(bitmap->bitmap & 0xff){
        return ucBitMapTable[(bitmap->bitmap >>  0) & 0xff] + 0;
    }else if(bitmap->bitmap & 0xff00) {
        return ucBitMapTable[(bitmap->bitmap >>  8) & 0xff] + 8;
    }else if (bitmap->bitmap & 0xff0000) {
        return ucBitMapTable[(bitmap->bitmap >> 16) & 0xff] + 16;
    }else if (bitmap->bitmap & 0xff000000) {
        return ucBitMapTable[(bitmap->bitmap >> 24) & 0xff] + 24;
    }else{
        return bit_map_pos_count_get();
    }
}

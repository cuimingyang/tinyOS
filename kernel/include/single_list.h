#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///> 单向链表结点
typedef struct _tNode {
    struct _tNode * ptNext;                  ///< 下个结点
}NODE_S;


///> 单向链表
typedef struct _tSlist {
    NODE_S * tHeadNode;                     ///<  第一个结点
    NODE_S * tTailNode;                     ///<  最后一个结点
    UINT_T uiNodeCount;                     ///<  结点数量
}SINGLE_LIST_S;

extern VOID single_list_create(IN SINGLE_LIST_S *ptList);                           ///< 创建单向链表
extern VOID single_list_insert_head(IN SINGLE_LIST_S *ptList, IN NODE_S * ptNode);  ///< 单向链表头插
extern VOID single_list_insert_tail(IN SINGLE_LIST_S *ptList, IN NODE_S * ptNode);  ///< 单向链表尾插
extern NODE_S *single_list_remove_head_node(IN SINGLE_LIST_S *ptList);              ///< 删除单向链表头节点
extern UINT_T single_list_get_node_num(IN SINGLE_LIST_S *ptList);                   ///< 获取链表节点个数
extern NODE_S *single_list_get_head_node(IN SINGLE_LIST_S *ptList);                 ///< 获取链表头节点
extern NODE_S *single_list_get_tail_node(IN SINGLE_LIST_S *ptList);                 ///< 获取链表尾节点


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SINGLE_LIST_H__ */

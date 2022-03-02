#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


///< 双向链表结点数据结构
typedef struct _tNode {
    struct _tNode *ptPrevNode;            ///< 前一结点
    struct _tNode *ptNextNode;            ///< 后一结点
}NODE_S;


///< 双向链表数据结构
typedef struct _tList {
    NODE_S tHeadNode;
    UINT_T uiNodeCount;
}DOUBLE_LIST_S;


extern VOID double_list_create(IN DOUBLE_LIST_S *ptList);                                                                ///< 创建链表
extern UINT_T double_list_get_node_num(IN DOUBLE_LIST_S *ptList);                                                        ///< 获取链表中结点的数量
extern NODE_S *double_list_get_head_node(IN DOUBLE_LIST_S *ptList);                                                      ///< 获取链表中头结点
extern NODE_S *double_list_get_tail_node(IN DOUBLE_LIST_S *ptList);                                                      ///< 获取链表中尾节点
extern NODE_S *double_list_get_prev_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode);                                   ///< 获取链表中指定结点的前一结点
extern NODE_S *double_list_get_next_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode);                                   ///< 获取链表中指定结点的后一结点
extern VOID double_list_remove_all_node(IN DOUBLE_LIST_S *ptList);                                                       ///< 清空链表中的所有结点
extern VOID double_list_insert_head_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode);                                   ///< 将节点插入链表头部
extern VOID double_list_insert_tail_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode);                                   ///< 将节点插入链表尾部
extern NODE_S *double_list_remove_head_node(IN DOUBLE_LIST_S *ptList);                                                   ///< 移除链表头结点
extern VOID double_list_insert_after_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNodeAfter, IN NODE_S *ptNodeToInsert);  ///< 将指定结点插入到某个结点之后
extern VOID double_list_remove_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode);                                        ///< 移除链表中指定节点


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DOUBLE_LIST_H__ */
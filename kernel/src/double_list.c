/*
 * @brief: 双向链表数据结构
 * @author: cuimy
 * @email: 2604325078@qq.com
 * @date: 2022-02-27
 * @Copyright: 
 */

#include "platform_adapt_type.h"
#include "platform_adapt_log.h"

/**
 * @brief: 初始化链表
 * @param：ptList 等待初始化的链表
 * @return：none
 */
VOID double_list_create(IN DOUBLE_LIST_S *ptList)
{
    ptList->tHeadNode.ptNextNode = &(ptList->tHeadNode);
    ptList->tHeadNode.ptPrevNode = &(ptList->tHeadNode);
    ptList->uiNodeCount = 0;
}

/**
 * @brief: 返回链表中结点的数量
 * @param: ptList 查询的链表
 * @return: 结点数量
 */
UINT_T double_list_get_node_num(IN DOUBLE_LIST_S *ptList)
{
    return ptList->uiNodeCount;
}

/**
 * @brief: 返回链表中首个结点
 * @param: list 查询的链表
 * @return: 头结点，如果链表空，返回NULL
 */
NODE_S *double_list_get_head_node(IN DOUBLE_LIST_S *ptList)
{
    NODE_S *ptNode = NULL;

    if(0 != ptList->uiNodeCount) {
        ptNode = ptList->tHeadNode.ptNextNode;
    }
    return ptNode;
}

/**
 * @brief: 返回链表中最后结点
 * @param: list 查询的链表
 * @return: 尾结点，如果链表空，返回NULL
 */
NODE_S *double_list_get_tail_node(IN DOUBLE_LIST_S *ptList)
{
    NODE_S *ptNode = NULL;

    if (ptList->uiNodeCount != 0) {
        ptNode = ptList->tHeadNode.ptPrevNode;
    }
    return ptNode;
}

/**
 * @brief: 返回链表中指定结点的前一结点
 * @param：ptList 查询的链表
 * @param：ptNode 查询的结点
 * @return: 前一结点，如果没有，返回NULL
 */
NODE_S *double_list_get_prev_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode)
{
    if ((ptNode->ptPrevNode == &ptList->tHeadNode) || (ptNode->ptPrevNode == ptNode)) {
        return NULL;
    } else {
        return ptNode->ptPrevNode;
    }
}

/**
 * @brief: 返回链表中指定结点的后一结点
 * @param: ptList 查询的链表
 * @param: ptNode 查询的结点
 * @return: 后一结点，如果没有，返回NULL
 */
NODE_S *double_list_get_next_node(IN DOUBLE_LIST_S *ptList, IN NODE_S *ptNode)
{
    if ((ptNode->ptNextNode == &ptList->tHeadNode) || (ptNode->ptNextNode == &ptList->tHeadNode)) {
        return NULL;
    } else {
        return ptNode->ptNextNode;
    }
}

/**
 * @brief: 清空链表中的所有结点
 * @param: ptList 等待清空的链表
 * @return: none
 */
VOID double_list_remove_all_node(DOUBLE_LIST_S *ptList)
{
    UINT_T uiCount;
    NODE_S *ptNextNode;

    // 遍历所有的结点
    ptNextNode = ptList->tHeadNode.ptNextNode;
    for (uiCount = ptList->uiNodeCount; uiCount != 0; uiCount--) {
        // 先纪录下当前结点，和下一个结点
        // 必须纪录下一结点位置，因为在后面的代码中当前结点的next会被重置
        NODE_S *ptCurrNode = ptNextNode;
        ptNextNode = ptNextNode->ptNextNode;

        // 重置结点自己的信息
        ptCurrNode->ptNextNode = ptCurrNode;
        ptCurrNode->ptPrevNode = ptCurrNode;
    }

    ptList->tHeadNode.ptNextNode = &(ptList->tHeadNode);
    ptList->tHeadNode.ptPrevNode = &(ptList->tHeadNode);
    ptList->uiNodeCount = 0;
}

/**
 * @brief: 将指定结点插入到链表开始处
 * @param: ptList 操作的链表
 * @param: ptNode 待插入的结点
 * @return: none
 */
VOID double_list_insert_head_node(DOUBLE_LIST_S *ptList, NODE_S *ptNode)
{
    ptNode->ptPrevNode = ptList->tHeadNode.ptNextNode->ptPrevNode;
    ptNode->ptNextNode = ptList->tHeadNode.ptNextNode;

    ptList->tHeadNode.ptNextNode->ptPrevNode = ptNode;
    ptList->tHeadNode.ptNextNode = ptNode;
    ptList->uiNodeCount++;
}

/**
 * @brief: 将指定结点插入到链表最后
 * @param: ptList 操作的链表
 * @param: ptNode 待插入的结点
 * @return: none
 */
VOID double_list_insert_tail_node(DOUBLE_LIST_S *ptList, NODE_S *ptNode)
{
    ptNode->ptNextNode = &(ptList->tHeadNode);
    ptNode->ptPrevNode = ptList->tHeadNode.ptPrevNode;

    ptList->tHeadNode.ptPrevNode->ptNextNode = ptNode;
    ptList->tHeadNode.ptPrevNode = ptNode;
    ptList->uiNodeCount++;
}

/**
 * @brief: 移除链表的第一个结点
 * @param: ptList 操作的链表
 * @return: 移除的结点，如果没有，返回NULL
 */
NODE_S *double_list_remove_head_node(DOUBLE_LIST_S *ptList)
{
    NODE_S *ptNode = NULL;

    if (ptList->uiNodeCount != 0) {
        ptNode = ptList->tHeadNode.ptNextNode;

        ptNode->ptNextNode->ptPrevNode = &(ptList->tHeadNode);
        ptList->tHeadNode.ptNextNode = ptNode->ptNextNode;
        ptList->uiNodeCount--;

        // 重置结点自己的信息
        ptNode->ptNextNode = ptNode;
        ptNode->ptPrevNode = ptNode;
    }
    return ptNode;
}

/**
 * @brief: 将指定结点插入到某个结点之后
 * @param: ptList 操作的链表
 * @param: ptNodeAfter 参考结点
 * @param: ptNodeToInsert 等待插入的结点
 * @return: none
 */
VOID double_list_insert_after_node(DOUBLE_LIST_S *ptList, NODE_S *ptNodeAfter, NODE_S *ptNodeToInsert)
{
    ptNodeToInsert->ptPrevNode = ptNodeAfter;
    ptNodeToInsert->ptNextNode = ptNodeAfter->ptNextNode;

    ptNodeAfter->ptNextNode->ptPrevNode = ptNodeToInsert;
    ptNodeAfter->ptNextNode = ptNodeToInsert;

    ptList->uiNodeCount++;
}

/**
 * @brief: 移除链表中指定结点
 * @param: ptList 操作的链表
 * @param: ptNode 等待队列的结点
 * @return: none
 */
VOID double_list_remove_node(DOUBLE_LIST_S *ptList, NODE_S *ptNode)
{
    ptNode->ptPrevNode->ptNextNode = ptNode->ptNextNode;
    ptNode->ptNextNode->ptPrevNode = ptNode->ptPrevNode;
    ptList->uiNodeCount--;

    ///> 重置结点自己的信息
    ptNode->ptNextNode = ptNode;
    ptNode->ptPrevNode = ptNode;
}

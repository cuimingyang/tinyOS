/*
 * @brief: 单向链表数据结构
 * @author: cuimy
 * @email: 2604325078@qq.com
 * @date: 2022-02-27
 * @Copyright: 
 */

#include "platform_adapt_type.h"
#include "platform_adapt_log.h"


/**
 * @brief: 初始化单链表
 * @param：ptList 单链表
 * @retval: none
 */
VOID single_list_create(IN SINGLE_LIST_S *ptList) 
{
    ptList->tHeadNode = NULL;
    ptList->tTailNode = NULL;
    ptList->uiNodeCount = 0;
}

/**
 * @brief: 获取单链表结点数量
 * @param： ptList 查询的单链表
 * @return： 结点数量
 */
UINT_T single_list_get_node_num(IN SINGLE_LIST_S *ptList)
{
    return ptList->uiNodeCount;
}

/**
 * @brief: 获取单链表的第一个结点
 * @param：ptList 查询的单链表
 * @return：第一个结点，如果没有，返回0
 */
NODE_S *single_list_get_head_node(IN SINGLE_LIST_S *ptList)
{
    return ptList->tHeadNode;
}

/**
 * @brief: 获取单链表的最后一个结点
 * @param： ptList 查询的单链表
 * @return： 最后一个结点，如果没有，返回0
 */
NODE_S *single_list_get_tail_node(IN SINGLE_LIST_S *ptList)
{
    return ptList->tTailNode;
}

/**
 * @brief: 将结点添加到链表表头
 * @param：ptList 操作的链表
 * @param：ptNode 待插入的结点
 * @return：none
 */
VOID single_list_insert_head(IN SINGLE_LIST_S *ptList, NODE_S * ptNode)
{
    if (ptList->uiNodeCount == 0) {
        ptList->tHeadNode = ptNode;
        ptList->tTailNode = ptNode;
        ptList->uiNodeCount = 1;
    } else {
        ptNode->ptNext = ptList->tHeadNode;
        ptList->tHeadNode = ptNode;
        ptList->uiNodeCount++;
    }
}

/**
 * @brief: 将结点插入到链表尾部
 * @param：ptList 操作的链表
 * @param：ptNode 待插入的结点
 * @return：none
 */
VOID single_list_insert_tail(IN SINGLE_LIST_S *ptList, IN NODE_S * ptNode)
{
    if (ptList->uiNodeCount == 0) {
        ptList->tHeadNode = ptNode;
        ptList->tTailNode = ptNode;
        ptList->uiNodeCount = 1;
    } else {
        ptList->tTailNode->ptNext = ptNode;
        ptNode->ptNext = ptNode;
        ptList->tTailNode = ptNode;
        ptList->uiNodeCount++;
    }
}

/**
 * @brief:移除链表的首个结点
 * @param：ptList 操作的链表
 * @return：移除的结点，如果没有，返回0
 */
NODE_S *single_list_remove_head_node(IN SINGLE_LIST_S *ptList)
{
    switch (ptList->uiNodeCount) {
        case 0:
            return NULL;
        case 1: {
            NODE_S *tRemoveNode = ptList->tHeadNode;
            tRemoveNode->ptNext = tRemoveNode;

            ptList->tHeadNode = NULL;
            ptList->tTailNode = NULL;
            ptList->uiNodeCount = 0;
            return tRemoveNode;
        }
        default: {
            NODE_S *tRemoveNode = ptList->tHeadNode;

            ptList->tHeadNode = tRemoveNode->ptNext;
            tRemoveNode->ptNext = tRemoveNode;
            ptList->uiNodeCount--;
            return tRemoveNode;
        }

    }
}

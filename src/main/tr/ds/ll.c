/**
 * This file is a part of ThetaRush.
 *
 * ThetaRush is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ThetaRush is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 *
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils/utils.h"

#include "tr/ds/ll.h"

static trLLMemHeap_t trLLMemHeap; /**< Global memory pool instance */
static trLLInterface_t trLL;      /**< Global module interface */

static int
trLLFindFreeSlot (void)
{
  for (int i = 0; i < __TR_LL_GUARD_SIZE; i++)
    {
      if (trLLMemHeap.guard[i] != 0xFFFFFFFF)
        {
          for (int j = 0; j < 32; j++)
            {
              if (!(trLLMemHeap.guard[i] & (1 << j)))
                {
                  int index = i * 32 + j;
                  if (index >= TR_LL_HEAP_SIZE)
                    continue;
                  return index;
                }
            }
        }
    }
  return -1;
}

/**
 * @brief Allocate node from memory heap
 * @return trLLNode_t* Allocated node, NULL if heap full
 */
trLLNode_t *
trLLHeapAllocNode (void)
{
  int index = trLLFindFreeSlot ();
  if (index == -1)
    return NULL;

  int guardIdx = index / 32;
  int bitPos = index % 32;
  trLLMemHeap.guard[guardIdx] |= (1 << bitPos);

  trLLNode_t *node = &trLLMemHeap.memPool[index];
  node->id = (uint32_t)index;
  node->pd = NULL;
  node->next = node->prev = NULL;
  return node;
}

/**
 * @brief Release node back to memory heap
 * @param[in] node Node to release
 */
void
trLLHeapFreeNode (trLLNode_t *node)
{
  if (node < trLLMemHeap.memPool
      || node >= &trLLMemHeap.memPool[TR_LL_HEAP_SIZE])
    return;

  int index = node - trLLMemHeap.memPool;
  int guardIdx = index / 32;
  int bitPos = index % 32;
  trLLMemHeap.guard[guardIdx] &= ~(1 << bitPos);
}

/**
 * @brief Create new empty list
 * @return trLL_t* List handle, NULL if allocation fails
 */
trLL_t *
trLLCreate (void)
{
  trLLNode_t *sentinel = trLLHeapAllocNode ();
  if (!sentinel)
    return NULL;

  sentinel->id = 0xFFFFFFFF;
  sentinel->len = 0;
  sentinel->next = sentinel;
  sentinel->prev = sentinel;
  return sentinel;
}

/**
 * @brief Destroy entire list
 * @param head Double pointer to list handle
 */
void
trLLDestroy (trLL_t **head)
{
  if (!head || !*head)
    return;
  trLL_t *sentinel = *head;

  // Remove all data nodes
  trLLNode_t *current = sentinel->next;
  while (current != sentinel)
    {
      trLLNode_t *temp = current;
      current = current->next;
      trLLMemHeap.free (temp);
    }

  // Release sentinel node
  trLLMemHeap.free (sentinel);
  *head = NULL;
}

/**
 * @brief Append a new node to list tail
 * @param[in] head List handle
 * @param[in] data Data payload pointer
 * @param[out] id Output parameter for new node ID
 * @return 0 on success, -1 on failure
 */
int
trLLPushBack (trLL_t *head, void *data, uint32_t *id)
{
  if (!head || head->id != 0xFFFFFFFF)
    return -1;

  trLLNode_t *newNode = trLLMemHeap.new ();
  if (!newNode)
    return -1;

  newNode->pd = data;
  newNode->prev = head->prev;
  newNode->next = head;

  head->prev->next = newNode;
  head->prev = newNode;
  head->len++; // Update cache

  if (id)
    *id = newNode->id;
  return 0;
}

/**
 * @brief Find node by memory pool index
 * @param[in] head List handle
 * @param[in] id Memory pool index to find
 * @return trLLNode_t* Found node, NULL if not in list
 */
trLLNode_t *
trLLFindNode (trLL_t *head, uint32_t id)
{
  if (!head || id >= TR_LL_HEAP_SIZE)
    return NULL;

  // Verify node is allocated
  int guardIdx = id / 32;
  int bitPos = id % 32;
  if (!(trLLMemHeap.guard[guardIdx] & (1 << bitPos)))
    return NULL;

  trLLNode_t *node = &trLLMemHeap.memPool[id];
  trLLNode_t *cur = head->next;

  // verify if this id belong to the current head
  while (cur != NULL)
    {
      if (cur->next == node)
        return node;

      cur = cur->next;
    }

  return NULL;
}

/**
 * @brief Remove node from list by ID
 * @param[in] head List handle
 * @param[in] id Target node ID
 * @return 0 if node found and removed, 1 otherwise
 */
int
trLLPopNode (trLL_t *head, uint32_t id)
{
  if (!head || id >= TR_LL_HEAP_SIZE)
    return 1;

  // Verify node exists in memory pool
  int guardIdx = id / 32;
  int bitPos = id % 32;
  if (!(trLLMemHeap.guard[guardIdx] & (1 << bitPos)))
    return 1;

  trLLNode_t *node = trLLFindNode (head, id);

  if (!node)
    return 1;

  if (node == head)
    {
      if (node->next == NULL && node->prev == NULL)
        {
          trLLMemHeap.free (node);
          return 0;
        }
      else
        return 1;
    }

  node->prev->next = node->next;
  node->next->prev = node->prev;
  trLLMemHeap.free (node);

  head->len--;
  return 0;
}

/**
 * @brief Get the number of nodes in a linear linked list
 * @param[in] head List handle
 * @return uint32_t Number of data nodes (0 if invalid list)
 */
uint32_t
trLLGetLength (trLL_t *head)
{
  if (!head || head->id != 0xFFFFFFFF)
    return 0;

  uint32_t count = 0;
  trLLNode_t *current = head->next;

  while (current != head)
    {
      count++;
      current = current->next;
    }
  return count;
}

/**
 * @brief Get list length with direction control
 * @param[in] head List handle
 * @param[in] dir Traversal direction (unused for linear list, reserved for
 * future)
 * @return uint32_t Number of data nodes, 0 for invalid list
 */
uint32_t
trLLGetLengthEx (trLL_t *head, trLLDirection_t dir)
{
  UNUSED (dir);

  // Validate list handle and sentinel marker
  if (!head || head->id != 0xFFFFFFFF)
    {
      return 0;
    }

  // Return cached length from sentinel node
  return head->len;
}

/**
 * @brief Traverse linear list with automatic length limit
 * @param[in] head List handle
 * @param[in] visit Node processing callback
 * @param[in] dir Traversal direction
 * @return Number of nodes visited
 */
uint32_t
trLLTraverse (trLL_t *head, void (*visit) (trLLNode_t *), trLLDirection_t dir)
{
  const uint32_t maxNodes = trLLGetLengthEx (head, dir);
  if (maxNodes == 0)
    return 0;

  uint32_t count = 0;
  trLLNode_t *current
      = (dir == TR_LL_DIRECTION_FORWARD) ? head->next : head->prev;

  while (current != head && count < maxNodes)
    {
      visit (current);
      current
          = (dir == TR_LL_DIRECTION_FORWARD) ? current->next : current->prev;
      count++;
    }
  return count;
}

/**
 * @brief Create circular linked list with specified length
 * @return trLL_t* List handle, NULL if creation fails
 */
trLL_t *
trCLLCreate (void)
{
  trLL_t *head = trLLCreate ();
  if (!head)
    return NULL;

  head->next->prev = head->prev;
  head->prev->next = head->next;

  return head;
}

/**
 * @brief Check if a list has circular linkage
 * @param[in] head List handle
 * @return true if circular, false if linear or invalid
 */
bool
trCLLIf (trLL_t *head)
{
  if (!head || head->id != 0xFFFFFFFF)
    return false;

  trLLNode_t *slow = head->next;
  trLLNode_t *fast = head->next;

  if (slow == head)
    return false;

  while (fast != head && fast->next != head)
    {
      slow = slow->next;
      fast = fast->next->next;

      if (slow == fast)
        return true;
    }
  return false;
}

/**
 * @brief Destroy a circular linked list and release all resources
 * @param[in] head Double pointer to the list handle
 */
void
trCLLDestroy (trLL_t **head)
{
  /* Parameter validation */
  if (!head || !*head)
    return;

  trLL_t *sentinel = *head;

  /* Verify sentinel node */
  if (sentinel->id != 0xFFFFFFFF)
    {
      *head = NULL;
      return;
    }

  /* Break circular linkage if necessary */
  if (trCLLIf (sentinel))
    {
      /* Restore linear connection */
      trLLNode_t *first = sentinel->next;
      trLLNode_t *last = sentinel->prev;

      first->prev = sentinel;
      last->next = sentinel;
    }

  /* Release all data nodes */
  trLLNode_t *current = sentinel->next;
  while (current != sentinel)
    {
      trLLNode_t *temp = current;
      current = current->next;

      /* Clear node references */
      temp->prev = NULL;
      temp->next = NULL;

      /* Return to memory pool */
      trLLMemHeap.free (temp);
    }

  /* Clear sentinel references */
  sentinel->next = sentinel;
  sentinel->prev = sentinel;

  /* Release sentinel node */
  trLLMemHeap.free (sentinel);

  /* Nullify handle */
  *head = NULL;
}

/**
 * @brief Push node to circular list tail
 * @param[in] head List handle
 * @param[in] id Node identifier
 * @param[in] data Payload data pointer
 * @return 0 on success, -1 on failure
 */
int
trCLLPushBack (trLL_t *head, void *data, uint32_t *id)
{
  if (!head || !trCLLIf (head))
    return -1;

  trLLNode_t *newNode = trLLMemHeap.new ();
  if (!newNode)
    return -1;

  newNode->pd = data;

  // Insert before sentinel node
  newNode->prev = head->prev;
  newNode->next = head;
  head->prev->next = newNode;
  head->prev = newNode;

  // Maintain circular connection
  if (head->next == head)
    {
      head->next = newNode;
      newNode->prev = head->prev;
    }
  head->len++;

  if (id)
    *id = newNode->id;

  return 0;
}

/**
 * @brief Find node in circular list by ID
 * @param[in] head List handle
 * @param[in] id Target node ID
 * @return trLLNode_t* Found node, NULL if not found
 */
trLLNode_t *
trCLLFindNode (trLL_t *head, uint32_t id)
{
  if (!head || !trCLLIf (head) || id >= TR_LL_HEAP_SIZE)
    return NULL;

  // Verify node is allocated
  int guardIdx = id / 32;
  int bitPos = id % 32;
  if (!(trLLMemHeap.guard[guardIdx] & (1 << bitPos)))
    return NULL;

  trLLNode_t *node = &trLLMemHeap.memPool[id];
  trLLNode_t *cur = head->next;
  uint16_t count = 0;

  while (cur != head && count < head->len)
    {
      if (cur->next == node)
        return node;
      count++;
      cur = cur->next;
    }

  return NULL;
}

/**
 * @brief Remove node from circular list by ID
 * @param[in] head List handle
 * @param[out] id Target node ID
 * @return 0 if node found and removed, 1 otherwise
 */
int
trCLLPopNode (trLL_t *head, uint32_t id)
{
  if (!head || !trCLLIf (head) || id >= TR_LL_HEAP_SIZE)
    return 1;

  // Verify node exists in memory pool
  int guardIdx = id / 32;
  int bitPos = id % 32;
  if (!(trLLMemHeap.guard[guardIdx] & (1 << bitPos)))
    return 1;

  trLLNode_t *node = trCLLFindNode (head, id);

  if (!node)
    return 1;

  if (node == head)
    {
      if (node->next == node && node->prev == node)
        {
          trLLMemHeap.free (node);
          return 0;
        }
      else
        return 1;
    }

  node->prev->next = node->next;
  node->next->prev = node->prev;

  // Update head connections if removing edge node
  if (head->next == node)
    head->next = node->next;
  if (head->prev == node)
    head->prev = node->prev;

  trLLMemHeap.free (node);

  head->len--;
  return 0;
}

/**
 * @brief Get the number of nodes in a circular linked list
 * @param[in] head List handle
 * @return uint32_t Number of data nodes (0 if invalid list)
 */
uint32_t
trCLLGetLength (trLL_t *head)
{
  if (!head || head->id != 0xFFFFFFFF || !trCLLIf (head))
    return 0;

  uint32_t count = 0;
  trLLNode_t *current = head->next;

  while (current != head)
    {
      count++;
      current = current->next;
    }
  return count;
}

/**
 * @brief Get circular list length with direction control
 * @param[in] head List handle
 * @param[in] dir Traversal direction (unused, consistency only)
 * @return uint32_t Number of data nodes, 0 for invalid list
 */
uint32_t
trCLLGetLengthEx (trLL_t *head, trLLDirection_t dir)
{
  UNUSED (dir);
  // Use cached length if valid circular list
  if (head && head->id == 0xFFFFFFFF && trCLLIf (head))
    return head->len;
  return 0;
}

/**
 * @brief Traverse circular list with automatic length limit
 * @param[in] head List handle
 * @param[in] visit Node processing callback
 * @param[in] dir Traversal direction
 * @return Number of nodes visited
 */
uint32_t
trCLLTraverse (trLL_t *head, void (*visit) (trLLNode_t *), trLLDirection_t dir)
{
  const uint32_t maxNodes = trCLLGetLengthEx (head, dir);
  if (maxNodes == 0)
    return 0;

  uint32_t count = 0;
  trLLNode_t *current
      = (dir == TR_LL_DIRECTION_FORWARD) ? head->next : head->prev;
  trLLNode_t *start = current;

  do
    {
      visit (current);
      current
          = (dir == TR_LL_DIRECTION_FORWARD) ? current->next : current->prev;
      count++;
    }
  while (current != start && count < maxNodes);

  return count;
}

/**
 * @brief Break circular linkage to linear list
 * @param[in] head List handle
 * @return 0 if successfully broken, 1 otherwise
 */
int
trLCLLBreak (trLL_t *head)
{
  if (!head || head->id != 0xFFFFFFFF || !trCLLIf (head))
    return 1;

  trLLNode_t *first = head->next;
  trLLNode_t *last = head->prev;

  // Restore normal linkage
  first->prev = head;
  last->next = head;
  return 0;
}

/**
 * @brief Initialize ThetaRush linked list interface
 */
void
trLLInterfaceInit (void)
{
  trLLMemHeap_t *pm = &trLLMemHeap;
  trLLInterface_t *pInterface = &trLL;

  // Memory heap initialization
  for (int i = 0; i < __TR_LL_GUARD_SIZE; ++i)
    {
      pm->guard[i] = 0;
    }
  pm->new = trLLHeapAllocNode;
  pm->free = trLLHeapFreeNode;

  pInterface->heap = pm;

  /* Bind linear list functions */
  pInterface->create = trLLCreate;
  pInterface->destroy = trLLDestroy;
  pInterface->pushBack = trLLPushBack;
  pInterface->find = trLLFindNode;
  pInterface->popNode = trLLPopNode;
  pInterface->getLength = trLLGetLength;
  pInterface->getLengthEx = trLLGetLengthEx;
  pInterface->traverse = trLLTraverse;

  /* Bind circular list functions */
  pInterface->cllCreate = trCLLCreate;
  pInterface->cllIf = trCLLIf;
  pInterface->cllDestroy = trCLLDestroy;
  pInterface->cllPushBack = trCLLPushBack;
  pInterface->cllFindNode = trCLLFindNode;
  pInterface->cllPopNode = trCLLPopNode;
  pInterface->cllGetLength = trCLLGetLength;
  pInterface->cllGetLengthEx = trCLLGetLengthEx;
  pInterface->cllTraverse = trCLLTraverse;
  pInterface->cllBreak = trLCLLBreak;
}

trLLInterface_t *
trLLInterfaceHandle (void)
{
  return &trLL;
}

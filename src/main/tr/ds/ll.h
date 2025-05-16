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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Direction enumeration for traversal
 */
typedef enum
{
  TR_LL_FORWARD, /**< Traverse from head to tail */
  TR_LL_BACKWARD /**< Traverse from tail to head */
} trLLDirection_t;

/* Node structure for doubly linked list */
typedef struct __trLLNode_s
{
  uint32_t id;               /**< Unique node identifier */
  void *pd;                  /**< Generic payload data pointer */
  struct __trLLNode_s *next; /**< Pointer to next node */
  struct __trLLNode_s *prev; /**< Pointer to previous node */
  uint32_t len; /**< Cached list length (valid in sentinel node) */
} trLLNode_t;

/** Linked list handle type */
typedef trLLNode_t trLL_t;

#if !defined(TR_LL_HEAP_SIZE)
#define TR_LL_HEAP_SIZE 128
#define __TR_LL_GUARD_SIZE (TR_LL_HEAP_SIZE / 32)
#endif

/* Memory heap management structure */
typedef struct __trLLMemHeap_s
{
  trLLNode_t memory[TR_LL_HEAP_SIZE]; /**< Preallocated node array */
  uint32_t guard[__TR_LL_GUARD_SIZE]; /**< Bitmap tracking usage */
  trLLNode_t *(*new) (void);          /**< Allocation function */
  void (*free) (trLLNode_t *);        /**< Deallocation function */
} trLLMemHeap_t;

/* Modular interface structure */
typedef struct __trLLModule_s
{
  trLLMemHeap_t *heap; /**< Associated memory heap */

  trLL_t *(*create) (void);                     /**< Create new list */
  int (*pushBack) (trLL_t *, uint32_t, void *); /**< Add node to list tail */
  bool (*popNode) (trLL_t *, uint32_t);         /**< Remove node by ID */
  trLLNode_t *(*find) (trLL_t *, uint32_t);     /**< Find node by ID */
  uint32_t (*getLength) (trLL_t *);             /**< Get linear list length */
  uint32_t (*getLengthEx) (
      trLL_t *, trLLDirection_t); /**< Get linear list length with direction */
  uint32_t (*traverse) (trLL_t *, void (*) (trLLNode_t *), trLLDirection_t);
  void (*destroy) (trLL_t **); /**< Destroy entire list */

  trLL_t *(*cllCreate) (uint8_t); /**< Create circular list */
  bool (*cllIf) (trLL_t *);       /**< Check circular linkage */
  int (*cllPushBack) (trLL_t *, uint32_t, void *);
  bool (*cllPopNode) (trLL_t *, uint32_t);
  trLLNode_t *(*cllFindNode) (trLL_t *, uint32_t);
  uint32_t (*cllGetLength) (trLL_t *); /**< Get circular list length */
  uint32_t (*cllGetLengthEx) (
      trLL_t *,
      trLLDirection_t); /**< Get circular list length with direction */
  uint32_t (*cllTraverse) (trLL_t *, void (*) (trLLNode_t *),
                           trLLDirection_t); /**< Safe traversal */
  bool (*cllBreak) (trLL_t *);               /**< Convert to linear */
  void (*cllRotate) (trLL_t *, int32_t);     /**< Rotate circular list */
  void (*cllDestroy) (trLL_t **);            /**< Circular list destruction */
} trLLInterface_t;

trLLNode_t *trLLHeapAllocNode (void);
void trLLHeapFreeNode (trLLNode_t *node);

trLL_t *trLLCreate (void);
int trLLPushNode (trLL_t *head, uint32_t id, void *data);
bool trLLPopNode (trLL_t *head, uint32_t id);
trLLNode_t *trLLFindNode (trLL_t *head, uint32_t id);
uint32_t trLLGetLength (trLL_t *head);
uint32_t trLLGetLengthEx (trLL_t *head, trLLDirection_t dir);
uint32_t trLLTraverse (trLL_t *head, void (*visit) (trLLNode_t *),
                       trLLDirection_t dir);
void trLLDestroy (trLL_t **head);

trLL_t *trCLLCreate (uint8_t count);
bool trCLLIf (trLL_t *head);
int trCLLPushBack (trLL_t *head, uint32_t id, void *data);
bool trCLLPopNode (trLL_t *head, uint32_t id);
trLLNode_t *trCLLFindNode (trLL_t *head, uint32_t id);
uint32_t trCLLGetLength (trLL_t *head);
uint32_t trCLLGetLengthEx (trLL_t *head, trLLDirection_t dir);
uint32_t trCLLTraverse (trLL_t *head, void (*visit) (trLLNode_t *),
                        trLLDirection_t dir);
bool trLCLLBreak (trLL_t *head);
void trLCLLRotate (trLL_t *head, int32_t steps);
void trCLLDestroy (trLL_t **head);

trLLInterface_t* trLLInterfaceHandle(void);

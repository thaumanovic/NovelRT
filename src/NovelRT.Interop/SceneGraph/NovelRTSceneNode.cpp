// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>
#include <list>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

std::list<std::shared_ptr<NovelRT::SceneGraph::SceneNode>> _sceneNodeCollection;
void(*_function)(NovelRTSceneNode) = NULL;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTSceneNode NovelRT_SceneNode_create() {
    _sceneNodeCollection.push_back(std::make_shared<SceneGraph::SceneNode>());
    return reinterpret_cast<NovelRTSceneNode>(_sceneNodeCollection.back().get());
}

int32_t NovelRT_SceneNode_getChildren(NovelRTSceneNode node, NovelRTSceneNodeSet* outputSet, const char** errorMessage) {
    if(node == nullptr|| outputSet == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet = new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
    *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getChildren();
    *outputSet = reinterpret_cast<NovelRTSceneNodeSet>(nodeSet);
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_getParents(NovelRTSceneNode node, NovelRTSceneNodeSet* outputSet, const char** errorMessage) {
    if(node == nullptr|| outputSet == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet = new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
    *nodeSet = reinterpret_cast<SceneGraph::SceneNode*>(node)->getParents();
    *outputSet = reinterpret_cast<NovelRTSceneNodeSet>(nodeSet);
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_insert(NovelRTSceneNode node, NovelRTSceneNode nodeToInsert, int32_t* outputResult, const char** errorMessage) {
    if(node == nullptr|| outputResult == nullptr || nodeToInsert == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
    *outputResult = static_cast<int32_t>(nodePointer->insert(reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this()));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_remove(NovelRTSceneNode node, NovelRTSceneNode nodeToRemove, int32_t* outputResult, const char** errorMessage) {
    if(node == nullptr|| outputResult == nullptr || nodeToRemove == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
    *outputResult = static_cast<int32_t>(nodePointer->remove(reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this()));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_isAdjacent(NovelRTSceneNode firstNode, NovelRTSceneNode secondNode, int32_t* outputResult, const char** errorMessage) {
    if(firstNode == nullptr|| secondNode == nullptr || outputResult == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
    *outputResult = static_cast<int32_t>(nodePointer->isAdjacent(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_traverseBreadthFirst(NovelRTSceneNode node, void(*action)(NovelRTSceneNode), const char** errorMessage) {
    if(node == nullptr|| action == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
    _function = action;
    nodePointer->traverseBreadthFirst(reinterpret_cast<std::function<void(std::shared_ptr<SceneGraph::SceneNode>)>&>(_function));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_traverseDepthFirst(NovelRTSceneNode node, void(*action)(NovelRTSceneNode), const char** errorMessage) {
    if(node == nullptr|| action == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node);
    _function = action;
    nodePointer->traverseDepthFirst(reinterpret_cast<std::function<void(std::shared_ptr<SceneGraph::SceneNode>)>&>(_function));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_canReach(NovelRTSceneNode firstNode, NovelRTSceneNode secondNode, int32_t* outputResult, const char** errorMessage) {
    if(firstNode == nullptr|| secondNode == nullptr || outputResult == nullptr) {
       if(errorMessage != nullptr) {
         *errorMessage = NovelRT_getErrMsgIsNullptr();
       }
       return NOVELRT_FAILURE;
     }

    auto firstNodePointer = reinterpret_cast<SceneGraph::SceneNode*>(firstNode);
    *outputResult = static_cast<int32_t>(firstNodePointer->canReach(reinterpret_cast<SceneGraph::SceneNode*>(secondNode)->shared_from_this()));
     return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNode_delete(NovelRTSceneNode node, const char** errorMessage) {
  if(node == nullptr) {
    if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
     }

  auto nodePointer = reinterpret_cast<SceneGraph::SceneNode*>(node)->shared_from_this();
  if(std::find(_sceneNodeCollection.begin(), _sceneNodeCollection.end(), nodePointer) == _sceneNodeCollection.end()) {
    if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsAlreadyDeletedOrRemoved();
      }
      return NOVELRT_FAILURE;
    }
    
    _sceneNodeCollection.remove(nodePointer);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeSet_delete(NovelRTSceneNodeSet nodeSet, const char** errorMessage) {
  if(nodeSet == nullptr) {
    if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
      }

  delete reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeSet_getSize(const NovelRTSceneNodeSet nodeSet, size_t* outputSize, const char** errorMessage) {
  if(nodeSet == nullptr || outputSize == nullptr) {
    if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
  
  *outputSize = reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet)->size();
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_SceneNodeSet_getSceneNodeFromIndex(const NovelRTSceneNodeSet nodeSet, size_t index, NovelRTSceneNode* outputSceneNode, const char** errorMessage) {
  if(nodeSet == nullptr || outputSceneNode == nullptr) {
    if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }
  auto cNodeSet = reinterpret_cast<std::set<std::shared_ptr<SceneGraph::SceneNode>>*>(nodeSet);
  *outputSceneNode = reinterpret_cast<NovelRTSceneNode&>(cNodeSet[index]);
  return NOVELRT_SUCCESS;
}

//Hidden bootstrapping method to act as "delegate" for C functions requiring `NovelRTSceneNode`
void SceneNodeFunctionInvoker(const std::shared_ptr<SceneGraph::SceneNode> node) {
    _function(reinterpret_cast<NovelRTSceneNode>(node.get()));
}

#ifdef __cplusplus
}
#endif
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTCATALOGUE_H
#define NOVELRT_NRTCATALOGUE_H

#include "../NrtInteropUtils.h"
#include "NrtComponentCache.h"
#include "NrtEcsUtils.h"
#include "NrtEntityCache.h"
#include "NrtUnsafeComponentView.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct CatalogueHandle* NrtCatalogue;

    NrtCatalogue Nrt_Catalogue_Create(size_t poolId, NrtComponentCache componentCache, NrtEntityCache entityCache);

    NrtResult Nrt_Catalogue_GetComponentViewById(NrtCatalogue catalogue,
                                                 NrtComponentTypeId componentId,
                                                 NrtUnsafeComponentView* outputResult);

    NrtUnsafeComponentView Nrt_Catalogue_GetComponentViewByIdUnsafe(NrtCatalogue catalogue,
                                                                    NrtComponentTypeId componentId);

    NrtEntityId Nrt_catalogue_CreateEntity(NrtCatalogue catalogue);

    NrtResult Nrt_Catalogue_DeleteEntity(NrtCatalogue catalogue, NrtEntityId entity);

    NrtResult Nrt_Catalogue_Destroy(NrtCatalogue catalogue);

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTCATALOGUE_H

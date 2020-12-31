// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_ECSUTILS_H
#define NOVELRT_ECS_ECSUTILS_H

#include "../Atom.h"
#include <cstdint>

namespace NovelRT::Ecs
{
    using EntityId = Atom;
    using ComponentTypeId = Atom;

    template <typename TComponent> [[nodiscard]] ComponentTypeId GetComponentTypeId() noexcept
    {
        static const Atom id = Atom::getNextComponentTypeId();
        return id;
    }
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_ECSUTILS_H
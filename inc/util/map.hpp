#pragma once

#include <unordered_map>
#include <optional>
#include <memory>

namespace umap
{
    template <typename K, typename V>
    std::optional<V> get(const std::unordered_map<K, V> &map, const K &key)
    {
        auto found = map.find(key);

        if (found == map.end())
            return {};

        return found->second;
    }
};
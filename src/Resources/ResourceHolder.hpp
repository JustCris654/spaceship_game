#ifndef TEXTURE_HOLDER_H_
#define TEXTURE_HOLDER_H_

#include <SFML/Graphics.hpp>

#include "textures.hpp"

#include <assert.h>
#include <iostream>
#include <map>

template <typename Resource, typename Identifier> class ResourceHolder {
  public:
    ResourceHolder();
    ~ResourceHolder();

    // load resources with loadFromFile(filename)
    void load(Identifier id, const std::string &filename);
    // load resources with loadFromFile with a second parameter
    template <typename Parameter>
    void load(Identifier id, const std::string &filename, Parameter secondaram);
    Resource &      get(Identifier id);
    const Resource &get(Identifier id) const;

  private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);
};

#include "ResourceHolder.inl"
#endif

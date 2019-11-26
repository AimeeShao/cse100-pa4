# Define ActorNode using function library()
actornode = library('ActorNode',
  sources: ['ActorNode.cpp', 'ActorNode.hpp'])

inc = include_directories('.')

actornode_dep = declare_dependency(include_directories: inc,
  link_with: actornode)
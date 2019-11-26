subdir('ActorNode')
subdir('MovieEdge')

# Define ActorGraph using function library()
actorgraph = library('ActorGraph',
  sources: ['ActorGraph.cpp', 'ActorGraph.hpp'],
  dependencies: [actornode_dep, movieedge_dep])

inc = include_directories('.')

actorgraph_dep = declare_dependency(include_directories: inc,
  link_with: actorgraph)
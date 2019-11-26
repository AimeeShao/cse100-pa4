# Define MovieEdge using function library()
movieedge = library('MovieEdge',
  sources: ['MovieEdge.cpp', 'MovieEdge.hpp'])

inc = include_directories('.')

movieedge_dep = declare_dependency(include_directories: inc,
  link_with: movieedge)
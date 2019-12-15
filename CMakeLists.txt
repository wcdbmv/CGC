cmake_minimum_required(VERSION 3.15)
project(CGC)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_compile_options(
	-Werror

	-Wall
	-Wextra
	-Wpedantic

	-Wcast-align
	-Wcast-qual
	-Wconversion
	-Wctor-dtor-privacy
	-Wenum-compare
	-Wfloat-equal
	-Wnon-virtual-dtor
	-Wold-style-cast
	-Woverloaded-virtual
	-Wredundant-decls
	-Wsign-conversion
	-Wsign-promo
)

set(
	SOURCES
	components/color_label/color_label.cpp
	components/draw_label/draw_label.cpp
	components/function_table_widget/function_table_widget.cpp
	function/expression/expression.cpp
	function/function/funciton.cpp
	function/function_parser/function_parser.cpp
	math/range/range.cpp
	math/transformation/dimensional_transformations.cpp
	math/transformation/transformation.cpp
	math/transformation/transformation_interface.cpp
	object/camera/camera.cpp
	surface/surface.cpp
	mainwindow.cpp
)

set(
	HEADERS
	components/color_label/color_label.hpp
	components/draw_label/draw_label.hpp
	components/function_table_widget/function_table_widget.hpp
	function/expression/expression.hpp
	function/exprtk/exprtk.hpp
	function/function/function.hpp
	function/function_parser/function_parser.hpp
	math/global/global.hpp
	math/grid/grid.hpp
	math/matrix/matrix.hpp
	math/matrix/matrix4x4.hpp
	math/matrix/rectangular_matrix.hpp
	math/range/range.hpp
	math/region/region.hpp
	math/transformation/dimensional_transformations.hpp
	math/transformation/transformation.hpp
	math/transformation/transformation_interface.hpp
	math/vector/homogeneous_vector3d.hpp
	math/vector/vector.hpp
	math/vector/vector3d.hpp
	object/camera/camera.hpp
	object/edge/edge.hpp
	object/face/face.hpp
	object/face/triangle_face.hpp
	object/mesh/mesh.hpp
	object/vertex/vertex.hpp
	scene/scene.hpp
	surface/surface.hpp
	mainwindow.hpp
)

add_executable(CGC ${SOURCES} ${HEADERS} main.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

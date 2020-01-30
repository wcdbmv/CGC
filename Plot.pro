#-------------------------------------------------
#
# Project created by QtCreator 2019-10-27T14:32:19
#
#-------------------------------------------------

QT	+= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
	components/color_label/color_label.cpp \
	components/draw_label/draw_label.cpp \
	components/function_table_widget/function_table_widget.cpp \
	components/grid_widget/grid_widget.cpp \
	function/expression/expression.cpp \
	function/function/funciton.cpp \
	function/function_parser/function_parser.cpp \
	math/range/range.cpp \
	math/transformation/dimensional_transformations.cpp \
	math/transformation/transformation.cpp \
	math/transformation/transformation_interface.cpp \
	object/camera/camera.cpp \
	render/cascade_renderer/cascade_renderer.cpp \
	render/solid_renderer/solid_renderer.cpp \
	surface/surface.cpp \
	main.cpp \
	mainwindow.cpp

HEADERS += \
	components/color_label/color_label.hpp \
	components/draw_label/draw_label.hpp \
	components/function_table_widget/function_table_widget.hpp \
	components/grid_widget/grid_widget.hpp \
	function/expression/expression.hpp \
	function/exprtk/exprtk.hpp \
	function/function/function.hpp \
	function/function_parser/function_parser.hpp \
	math/global/global.hpp \
	math/grid/grid.hpp \
	math/matrix/matrix.hpp \
	math/matrix/matrix4x4.hpp \
	math/matrix/rectangular_matrix.hpp \
	math/range/range.hpp \
	math/region/region.hpp \
	math/transformation/dimensional_transformations.hpp \
	math/transformation/transformation.hpp \
	math/transformation/transformation_interface.hpp \
	math/vector/homogeneous_vector3d.hpp \
	math/vector/vector.hpp \
	math/vector/vector3d.hpp \
	object/camera/camera.hpp \
	object/edge/edge.hpp \
	object/face/face.hpp \
	object/face/triangle_face.hpp \
	object/mesh/mesh.hpp \
	object/triangle/triangle.hpp \
	object/vertex/vertex.hpp \
	render/cascade_renderer/cascade_renderer.hpp \
	render/solid_renderer/solid_renderer.hpp \
	scene/scene.hpp \
	surface/surface.hpp \
	mainwindow.hpp

FORMS += \
	components/grid_widget/grid_widget.ui \
	mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

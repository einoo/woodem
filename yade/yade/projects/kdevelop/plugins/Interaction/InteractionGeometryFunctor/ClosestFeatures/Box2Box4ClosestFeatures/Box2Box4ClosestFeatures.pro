# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/Interaction/InteractionGeometryFunctor/ClosestFeatures/Box2Box4ClosestFeatures
# Target is a library:  

LIBS += -lBox \
        -lClosestFeatures \
        -lIntersections \
        -lMath \
        -lInteraction \
        -lMultiMethods \
        -rdynamic 
INCLUDEPATH = $(YADEINCLUDEPATH) 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../../../plugins/Geometry/GeometricalModel/Box/$(YADEDYNLIBPATH) \
               ../../../../../plugins/Interaction/InteractionGeometry/ClosestFeatures/$(YADEDYNLIBPATH) \
               ../../../../../toolboxes/ComputationalGeometry/Intersections/$(YADEDYNLIBPATH) \
               ../../../../../toolboxes/Libraries/Math/$(YADEDYNLIBPATH) \
               ../../../../../yade/Interaction/Interaction/$(YADEDYNLIBPATH) \
               ../../../../../toolboxes/Libraries/MultiMethods/$(YADEDYNLIBPATH) \
               ../../../../../yade/Geometry/$(YADEDYNLIBPATH) \
               ../../../../../yade/Interaction/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Box2Box4ClosestFeatures.hpp 
SOURCES += Box2Box4ClosestFeatures.cpp 

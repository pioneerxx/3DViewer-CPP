CFLAGS = -Wall -Werror -Wextra
CC = g++
CPPFLAGS = -lstdc++ -std=c++17 -pedantic
GFLAGS = --coverage
TFLAGS = -lgtest -lm -lpthread
ARFLAGS = rcs
OBJECTS = *.o
SOURCES_MODEL = Project/Model/Affine/Affine.cc Project/Model/Parser/Parser.cc Project/Model/Figure/Figure.cc Project/Model/Memento/Memento.cc Project/Model/Facade/Facade.cc Project/Model/SingletonModel/SingletonModel.cc
SOURCES_QT = Project/Controller/Controller/Controller.cc Project/Controller/SingletonController/SingletonController.cc Project/View/MainWindow/mainwindow.cc Project/View/GLWidget/glwidget.cc Project/View/SingletonView/SingletonView.cc Project/main.cc
SOURCES_TEST = Tests/tests.cc
HEADERS = Project/Model/Affine/Affine.h Project/Model/Parser/Parser.h Project/Model/Figure/Figure.h Project/Model/Memento/Memento.h Project/Model/Facade/Facade.h Project/Model/SingletonModel/SingletonModel.h \
	Project/Controller/Controller/Controller.h Project/Controller/SingletonController/SingletonController.h Project/View/MainWindow/mainwindow.h Project/View/GLWidget/glwidget.h Project/View/SingletonView/SingletonView.h

.PHONY: all install uninstall clean dvi dist tests 3dViewer.a leaks style start

all: clean 3dViewer.a

3dViewer.a: clean
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES_MODEL) -c
	ar $(ARFLAGS) 3dViewer.a $(OBJECTS)
	rm $(OBJECTS)

tests: 3dViewer.a
	$(CC) $(CPPFLAGS) $(FLAGS) -c $(SOURCES_TEST) -o tests.o
	$(CC) tests.o 3dViewer.a $(TFLAGS) -o test
	./test

leaks: 3dViewer.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $(GFLAGS) 3dViewer.a $(SOURCES_TEST) $(TFLAGS) -o test
	CK_FORK=no leaks --atExit -- ./test

clean:
	rm -rf 3dViewer.a test *.html *.gcda *.gcno gcov_test *.info report $(OBJECTS) *.dSYM *.css

style:
	clang-format -n $(SOURCES_MODEL) $(SOURCES_QT) $(SOURCES_TEST) $(HEADERS) -style=google

install:
	qmake -o Executables/Makefile Project/3dViewer.pro
	cd Executables && make

start:
	cd Executables/3dViewer.app/Contents/MacOS && ./3dViewer

uninstall:
	cd Executables && make clean
	cd Executables && rm -rf Makefile qmake_qmake_qm_files.qrc 3dViewer.app .qm .qmake.stash

dist:
	cd .. && tar -czf 3DViewer_v2.0.tgz src

dvi:
	open Manual/Manual.md

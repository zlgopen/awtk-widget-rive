import os
import platform
import scripts.app_helper as app

helper = app.Helper(ARGUMENTS)
CPPPATH=[
  os.path.join(helper.APP_ROOT, "src/rive-cpp/include"),
  os.path.join(helper.APP_ROOT, "src/rive-cpp/src"),
]

APP_CXXFLAGS = '-DAWTK=1 '
APP_CFLAGS=' -DRIVE_BUILD '

if platform.system() == 'Windows':
  APP_CXXFLAGS += ' /std:c++17 -DRIVE_BUILD '
else:
  APP_CXXFLAGS += ' -std=c++17 '

helper.add_cpppath(CPPPATH).add_cxxflags(APP_CXXFLAGS).add_cflags(APP_CFLAGS)
helper.set_dll_def('src/rive.def').set_libs(['rive']).call(DefaultEnvironment)

SConscriptFiles = ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
helper.SConscript(SConscriptFiles)
